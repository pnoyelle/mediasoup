#ifndef MS_RTC_UDP_SOCKET_HPP
#define MS_RTC_UDP_SOCKET_HPP

#include "common.hpp"
#include "handles/UdpSocketHandler.hpp"
#include <string>
#include <unordered_set>

namespace RTC
{
	class UdpSocket : public ::UdpSocketHandler
	{
	public:
		class Listener
		{
		public:
			virtual void OnUdpSocketPacketReceived(
			  RTC::UdpSocket* socket, const uint8_t* data, size_t len, const struct sockaddr* remoteAddr) = 0;

			std::unordered_set<std::string> remoteIpPorts;
		};

	public:
		UdpSocket(Listener* listener, std::string& ip);
		UdpSocket(Listener* listener, std::string& ip, uint16_t port);
		~UdpSocket() override;

		/* Pure virtual methods inherited from ::UdpSocketHandler. */
	public:
		void UserOnUdpDatagramReceived(const uint8_t* data, size_t len, const struct sockaddr* addr) override;
		uint32_t transports{ 0 };

	private:
		// Passed by argument.
		Listener* listener{ nullptr };
		bool fixedPort;
	};
} // namespace RTC

#endif
