#define MS_CLASS "RTC::UdpSocket"
// #define MS_LOG_DEV_LEVEL 3

#include "RTC/UdpSocket.hpp"
#include "Logger.hpp"
#include "RTC/PortManager.hpp"
#include "RTC/StunPacket.hpp"
#include "RTC/WebRtcTransport.hpp"
#include <string>

namespace RTC
{
	/* Instance methods. */
	static constexpr size_t StunBufferSize{ 65536 };
	static uint8_t StunBuffer[StunBufferSize];

	UdpSocket::UdpSocket(Listener* listener, std::string& ip)
	  : // This may throw.
	    ::UdpSocketHandler::UdpSocketHandler(PortManager::BindUdp(ip)), listener(listener),
	    fixedPort(false)
	{
		MS_TRACE();
	}

	UdpSocket::UdpSocket(Listener* listener, std::string& ip, uint16_t port)
	  : // This may throw.
	    ::UdpSocketHandler::UdpSocketHandler(PortManager::BindUdp(ip, port)), listener(listener),
	    fixedPort(true)
	{
		MS_TRACE();
	}

	UdpSocket::~UdpSocket()
	{
		MS_TRACE();

		if (!fixedPort)
		{
			PortManager::UnbindUdp(this->localIp, this->localPort);
		}
	}

	void UdpSocket::UserOnUdpDatagramReceived(const uint8_t* data, size_t len, const struct sockaddr* addr)
	{
		MS_TRACE();

		if (this->listener)
		{
			// Notify the reader.
			this->listener->OnUdpSocketPacketReceived(this, data, len, addr);
			return;
		}

		// No listener set, find it from mapping.
		std::string remoteIpPort;
		GetIpPort(addr, remoteIpPort);

		RTC::UdpSocket::Listener* listener = NULL;

		auto transportIter = RTC::WebRtcTransport::remoteIpPortToTransport.find(remoteIpPort);
		if (transportIter != RTC::WebRtcTransport::remoteIpPortToTransport.end())
		{
			listener = transportIter->second;
		}

		if (listener)
		{
			listener->OnUdpSocketPacketReceived(this, data, len, addr);
			return;
		}

		MS_WARN_DEV("no listener set for %s, parsing as STUN", remoteIpPort.c_str());

		// No item found in mapping, try parsing the packet as STUN data.
		RTC::StunPacket* packet = RTC::StunPacket::Parse(data, len);

		if (!packet)
		{
			MS_WARN_DEV("no listener set, ignoring wrong STUN packet received");
			return;
		}

		std::string username = packet->GetUsername();
		auto size            = username.find(":");
		if (size != std::string::npos)
		{
			username = username.substr(0, size);
		}
		MS_WARN_DEV("found '%s'", username.c_str());

		transportIter = RTC::WebRtcTransport::iceUserToTransport.find(username);
		if (transportIter == RTC::WebRtcTransport::iceUserToTransport.end())
		{
			// Reply 400.
			RTC::StunPacket* response = packet->CreateErrorResponse(400);
			response->Serialize(StunBuffer);
			this->Send(response->GetData(), response->GetSize(), addr, NULL);
			delete packet;
			delete response;
			return;
		}

		listener = transportIter->second;
		if (listener)
		{
			RTC::WebRtcTransport::remoteIpPortToTransport[remoteIpPort] = listener;
			listener->OnUdpSocketPacketReceived(this, data, len, addr);
		}

		delete packet;
	}

	void UdpSocket::GetIpPort(const struct sockaddr* addr, std::string& res)
	{
		int family = 0;
		std::string ip;
		uint16_t port;
		Utils::IP::GetAddressInfo(addr, family, ip, port);

		std::string id = ip + ":" + std::to_string(port);
		res            = std::move(id);
	}

} // namespace RTC
