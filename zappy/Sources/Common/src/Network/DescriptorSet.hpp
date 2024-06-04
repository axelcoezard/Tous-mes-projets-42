#pragma once

#include "Socket.hpp"

#include <cstdint>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class DescriptorSet
{
private:
	fd_set m_Set;
	int32_t m_MaxFd;

public:
	DescriptorSet() = default;

	DescriptorSet(const DescriptorSet& other)
	{
		m_Set = other.m_Set;
		m_MaxFd = other.m_MaxFd;
	}

	void Zero()
	{
		FD_ZERO(&m_Set);
		m_MaxFd = 0;
	}

	void Set(Socket* socket)
	{
		Set(socket->m_Instance);
	}

	void Set(int32_t fd)
	{
		FD_SET(fd, &m_Set);

		if (fd > m_MaxFd)
			m_MaxFd = fd;
	}

	bool IsSet(Socket* socket) const
	{
		return IsSet(socket->m_Instance);
	}

	bool IsSet(int32_t fd) const
	{
		return FD_ISSET(fd, &m_Set);
	}

	void Clear(Socket* socket)
	{
		Clear(socket->m_Instance);
	}

	void Clear(int32_t fd)
	{
		FD_CLR(fd, &m_Set);
	}

	int32_t GetMaxFd() const
	{
		return m_MaxFd;
	}

	fd_set& GetSet()
	{
		return m_Set;
	}
};
