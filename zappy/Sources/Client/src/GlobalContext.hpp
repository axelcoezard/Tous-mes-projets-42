/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlobalContext.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:04:04 by acoezard          #+#    #+#             */
/*   Updated: 2024/04/22 10:51:57 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Network/Socket.hpp"

struct GlobalContext
{
	bool appRunning = false;

	std::string m_Hostname = "127.0.0.1";
	int32_t m_Port;
	std::string m_Team;
	Socket* m_Server;

	int32_t width = -1;
	int32_t height = -1;

	int32_t m_Level;

	int32_t commandsRemaining = 10;
	std::queue<std::string> commandsQueue;

	bool waitingForResponse = false;
};
