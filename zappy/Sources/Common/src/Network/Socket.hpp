#pragma once

#include <cstdint>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

#define SOCKET_REUSE_ADRESS SO_REUSEADDR

class Socket
{
public:
	int32_t m_Instance;

	struct sockaddr_in m_Address;

	socklen_t m_AddressSize;

	Socket()
	{
		m_Instance = 0;
	}

	Socket(int32_t port, std::string address = "")
	{
		m_Instance = socket(AF_INET, SOCK_STREAM, 0);

		if (m_Instance < 0)
			throw std::runtime_error("Failed to create socket.");

		std::memset((char*) &m_Address, 0, sizeof(m_Address));
		m_Address.sin_family		=	AF_INET;
		m_Address.sin_port			=	htons(port);
		m_Address.sin_addr.s_addr	= 	address.size() > 0 ? inet_addr(address.c_str()) : htons(INADDR_ANY);

		m_AddressSize = sizeof(m_Address);
	}

	bool SetOption(int32_t name, int32_t value)
	{
		return setsockopt(m_Instance, SOL_SOCKET, name, &value, sizeof(int)) >= 0;
	}

	bool SetOption(int32_t name, struct timeval* value)
	{
		return setsockopt(m_Instance, SOL_SOCKET, name, value, sizeof(struct timeval)) >= 0;
	}

	bool Bind()
	{
		return bind(m_Instance, (struct sockaddr *) &m_Address, m_AddressSize) >= 0;
	}

	bool Listen()
	{
		return listen(m_Instance, 5) >= 0;
	}

	bool Disconnect()
	{
		return shutdown(m_Instance, SHUT_RDWR) >= 0;
	}

	bool Close()
	{
		if (m_Instance <= 0)
			return false;
		return close(m_Instance) >= 0;
	}

	bool Accept(Socket* dest)
	{
		int32_t newSocket = accept(m_Instance, (struct sockaddr *) &dest->m_Address, &dest->m_AddressSize);

		if (newSocket <= 0)
			return false;

		dest->m_Instance = newSocket;
		return true;
	}

	int32_t Receive(void* buffer, size_t length)
	{
		return recv(m_Instance, buffer, length, 0);
	}

	bool Connect()
	{
		return connect(m_Instance, (struct sockaddr *) &m_Address, m_AddressSize) >= 0;
	}

	bool IsSet() const
	{
		return m_Instance > 0;
	}

	int32_t Send(const void* buffer, size_t length)
	{
		int32_t flags = MSG_NOSIGNAL;
		#ifdef SO_NOSIGPIPE
			SetOption(SO_NOSIGPIPE, 1);
		#endif
		return send(m_Instance, buffer, length, flags);
	}
};
