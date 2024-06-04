/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketThread.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:31:00 by acoezard          #+#    #+#             */
/*   Updated: 2024/04/22 09:21:48 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Thread.hpp"

struct GlobalContext;

class SocketThread : public Thread
{
private:
	std::string m_Hostname = "127.0.0.1";
	int32_t m_Port;
	Socket* m_Socket;

	std::string m_Buffer;

public:
	SocketThread(GlobalContext* data, std::string hostname, int32_t port);
	~SocketThread();

	void Update() override;
	void ParseBufferLine(std::string line);
	std::pair<int16_t, int16_t> GetTypeFromBctLine(std::vector<std::string> args);
	std::thread* GetThread() override;
};
