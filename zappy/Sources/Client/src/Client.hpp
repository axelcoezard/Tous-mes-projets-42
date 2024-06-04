/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:29:56 by acoezard          #+#    #+#             */
/*   Updated: 2024/04/22 10:51:37 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "GlobalContext.hpp"

class Socket;
class WorldState;

struct Message {
	int orientation;
	std::string message;
};

typedef std::map<std::string, bool> State;

class Client
{
private:
	GlobalContext m_GlobalContext;
	WorldState* m_WorldState;

	State m_GoapStates;

	std::vector<Message> m_Messages;
	std::vector<std::string> group;
	std::string m_id;

public:
	Client();
	~Client();

	void Initialize(int argc, char **argv);
	void Start();

private:
	bool CanSendCommand();
	bool SendCommand(std::string command);
	std::string ReceiveCommand(bool wait_for_response = true);

	bool StartRitual();
	std::string GetInventory();
	std::string GetMap();
	void Goto(std::string target);
	void Goto(std::vector<std::string> target);
	void Idle();
	void ParseMessage();
	void ResetStates();
	bool IsTeamFull();
	void LookForFood();
};
