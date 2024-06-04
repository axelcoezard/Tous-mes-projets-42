/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:20:55 by acoezard          #+#    #+#             */
/*   Updated: 2024/05/07 09:47:24 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Utils.hpp"
#include "Game/Client.hpp"
#include "Commands/Command.hpp"

class Game;

class CommandManager
{
	private:
		std::map<std::string, std::pair<Command*, int32_t>>	m_Commands;

	public:
		CommandManager(void) = default;

		~CommandManager(void)
		{
			for (auto it = m_Commands.begin(); it != m_Commands.end(); it++)
				delete it->second.first;
			m_Commands.clear();
		}

		/**
		 * @brief Check if the CommandManager listen to a specific Command.
		 *
		 * @param cmd_name	The Command's name
		 * @return			true if the CommandManager is listening to the Command.
		 */
		bool Has(std::string cmd_name)
		{
			return m_Commands.count(Utils::str_tolower(cmd_name)) == 1;
		}

		/**
		 * @brief Register a Command to the CommandManager so it can be called later on.
		 *
		 * @param cmd_name	The command's name.
		 * @param cmd		The command's pointer.
		 */
		void On(std::string cmd_name, Command* cmd, int32_t delay)
		{
			std::string key = Utils::str_tolower(cmd_name);
			m_Commands[key].first = cmd;
			m_Commands[key].second = delay;
		}

		/**
		 * @brief Search a Command pointer by it's name and call it's CanBeQueued member method.
		 *
		 * @param cmd		The command's name.
		 * @param args		Every arguments of the command line.
		 * @param sender	The user that sent the command line.
		 * @return			true if the command can be queued, false otherwise.
		 */
		bool Verify(std::string cmd_name, std::vector<std::string> args, Game* game, Client* player)
		{
			if (!this->Has(cmd_name))
				return false;
			return m_Commands[Utils::str_tolower(cmd_name)].first->BeforeQueue(game, player, args);
		}

		/**
		 * @brief Search a Command pointer by it's name and call it's OnCommand member method.
		 *
		 * @param cmd		The command's name.
		 * @param args		Every arguments of the command line.
		 * @param sender	The user that sent the command line.
		 * @return			true if the command succeeded, false otherwise.
		 */
		bool Call(std::string cmd_name, std::vector<std::string> args, Game* game, Client* player)
		{
			if (!this->Has(cmd_name))
				return false;
			if (game->IsDebugMode())
				Console::Print("CALL", cmd_name + " pour " + std::to_string(player->GetSocketFd()), Console::BLUE);
			return m_Commands[Utils::str_tolower(cmd_name)].first->AfterQueue(game, player, args);
		}

		/**
		 * @brief Get the delay of a specific command.
		 *
		 * @param cmd_name	The command's name.
		 * @return			The delay of the command.
		 */
		int32_t GetDelay(std::string cmd_name)
		{
			if (!this->Has(cmd_name))
				return 0;
			return m_Commands[Utils::str_tolower(cmd_name)].second;
		}
};
