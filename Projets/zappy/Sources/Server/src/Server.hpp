/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:28:07 by acoezard          #+#    #+#             */
/*   Updated: 2024/05/07 14:08:42 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Clock.hpp"

#include "Network/Socket.hpp"
#include "Network/DescriptorSet.hpp"

#include "Game/Game.hpp"

#include "CommandManager.hpp"
#include "CommandSummary.hpp"
#include "CommandQueue.hpp"

#define SERVER_SUCCESS 1
#define SERVER_SKIP 0
#define SERVER_FAIL -1

class Server
{
private:
	int32_t m_Port;

	Socket m_Socket;
	Socket m_Clients[MAX_CLIENTS];

	DescriptorSet m_ReadSet;

	int32_t m_TickRate;
	int32_t m_MaxClientsPerTeamAtBeginning;
	bool m_DebugMode = false;

	CommandManager m_CommandManager;
	CommandQueue m_CommandQueue;

	Game* m_Game;
	Clock m_Clock;

public:
	void Initialize(int argc, char** argv);
	bool HasValidArguments(int argc, char** argv);
	bool isNumericAndPositive(const std::string& value);

	void Start();
	void Stop();

	int32_t ListenToClients();

	int32_t GetPort() const;
	bool IsDebugMode() const;
};
