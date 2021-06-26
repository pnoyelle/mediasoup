#define MS_CLASS "RTC::UdpSocket"
// #define MS_LOG_DEV_LEVEL 3

#include "RTC/UdpSocket.hpp"
#include "Logger.hpp"
#include "Utils.hpp"
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
		int family;
		std::string ip;
		uint16_t port;
		Utils::IP::GetAddressInfo(addr, family, ip, port);
		std::string remoteIpPort = ip + ":" + std::to_string(port);

		RTC::UdpSocket::Listener* listener = RTC::WebRtcTransport::GetFromRemoteIpPort(remoteIpPort);

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

		// Get transport from user name.
		std::string userName = packet->GetUsername();
		auto size            = userName.find(":");
		if (size != std::string::npos)
		{
			userName = userName.substr(0, size);
		}
		MS_WARN_DEV("found '%s'", userName.c_str());

		listener = RTC::WebRtcTransport::GetFromUserName(userName);
		if (listener == nullptr)
		{
			// Reply 400.
			RTC::StunPacket* response = packet->CreateErrorResponse(400);
			response->Serialize(StunBuffer);
			this->Send(response->GetData(), response->GetSize(), addr, NULL);
			delete packet;
			delete response;
			return;
		}
		else
		{
			RTC::WebRtcTransport::AddRemoteIpPort(remoteIpPort, listener);
			listener->OnUdpSocketPacketReceived(this, data, len, addr);
		}

		delete packet;
	}

} // namespace RTC
