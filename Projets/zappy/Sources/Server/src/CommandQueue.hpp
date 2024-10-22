/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandQueue.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:41:44 by acoezard          #+#    #+#             */
/*   Updated: 2024/04/22 08:53:17 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "CommandSummary.hpp"
#include "CommandManager.hpp"
#include "Game/Client.hpp"

class CommandQueue
{
private:
	std::vector<CommandSummary> m_Commands;

public:
	CommandQueue() = default;
	~CommandQueue() = default;

	void Push(CommandSummary cmd)
	{
		if (CanPushNewCommand(cmd.player))
			m_Commands.push_back(cmd);
	}

	void Execute(CommandManager* manager, Game* game)
	{
		for (size_t i = 0; i < m_Commands.size(); i++)
		{
			CommandSummary cmd = m_Commands[i];

			// Decrease the remaining delay and skip
			if (cmd.remainingDelay > 0)
			{
				m_Commands[i].remainingDelay--;
				continue;
			}

			// Execute the command if the player is connected
			if (cmd.player != nullptr && cmd.player->IsConnected())
				manager->Call(cmd.name, cmd.arguments, game, cmd.player);

			// Remove the command from the queue
			m_Commands.erase(m_Commands.begin() + i);

			i -= 1;
		}
	}

	bool CanPushNewCommand(Client* player) const
	{
		int32_t count = 0;
		for (size_t i = 0; i < m_Commands.size(); i++)
		{
			if (m_Commands[i].player->GetSocketFd() == player->GetSocketFd())
				count++;
		}
		return count < MAX_COMMANDS_PER_CLIENT;
	}

	bool IsEmpty() const
	{
		return m_Commands.size() == 0;
	}

	int32_t Size() const
	{
		return m_Commands.size();
	}
};
