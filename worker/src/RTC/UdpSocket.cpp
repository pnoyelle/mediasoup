#define MS_CLASS "RTC::UdpSocket"
// #define MS_LOG_DEV_LEVEL 3

#include "RTC/UdpSocket.hpp"
#include "Logger.hpp"
#include "RTC/PortManager.hpp"
#include "RTC/WebRtcTransport.hpp"
#include "RTC/StunPacket.hpp"
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

		MS_WARN_DEV("no listener set");

		// No listener set, find it from mapping.
		std::string peer_id;
		GetRemoteIpPort(addr, peer_id);

		RTC::UdpSocket::Listener* listener = NULL;

		auto peer_iter = RTC::WebRtcTransport::remoteIpPortToTransport.find(peer_id);
		if (peer_iter != RTC::WebRtcTransport::remoteIpPortToTransport.end())
		{
			listener = peer_iter->second;
		}

		if (listener)
		{
			listener->OnUdpSocketPacketReceived(this, data, len, addr);
			return;
		}

		// No item found in mapping, try parsing the packet as STUN data.
		RTC::StunPacket* packet = RTC::StunPacket::Parse(data, len);

		if (!packet)
		{
			MS_WARN_DEV("no listener set, ignoring wrong STUN packet received");
			return;
		}

		std::string userPass = packet->GetUsername();

		auto name_iter = RTC::WebRtcTransport::iceUserPassToTransport.find(userPass);
		if (name_iter == RTC::WebRtcTransport::iceUserPassToTransport.end())
		{
			// Reply 400.
			RTC::StunPacket* response = packet->CreateErrorResponse(400);
			response->Serialize(StunBuffer);
			this->Send(response->GetData(), response->GetSize(), addr, NULL);
			delete packet;
			delete response;
			return;
		}

		listener = name_iter->second;
		if (listener)
		{
			RTC::WebRtcTransport::remoteIpPortToTransport[peer_id] = listener;
			listener->OnUdpSocketPacketReceived(this, data, len, addr);
		}

		delete packet;
	}

	void UdpSocket::GetRemoteIpPort(const struct sockaddr* addr, std::string& peer_id)
	{
		int family = 0;
		std::string ip;
		uint16_t port;
		Utils::IP::GetAddressInfo(addr, family, ip, port);

		std::string id = ip + ":" + std::to_string(port);
		peer_id        = std::move(id);
	}

} // namespace RTC
