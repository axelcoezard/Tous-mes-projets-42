/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VoirCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:44:06 by acoezard          #+#    #+#             */
/*   Updated: 2024/04/22 09:17:15 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Command.hpp"
#include "Game/Game.hpp"
#include "Game/Map.hpp"
#include "Game/Client.hpp"

struct VoirCommand : public Command
{
	bool BeforeQueue(Game* game, Client* player, std::vector<std::string> args) override
	{
		(void) game;
		(void) player;
		(void) args;
		return true;
	}

	bool AfterQueue(Game* game, Client* player, std::vector<std::string> args) override
	{
		(void) args;
		Map* map = game->GetMap();
		int32_t level = player->GetLevel();

		int32_t directionX = player->GetDirection(0);
		int32_t directionY = player->GetDirection(1);

		std::vector<Client*> players = game->GetAllValidPlayers();

		std::stringstream ss;
		ss << "{ ";

		for (int16_t farAwayUnit = 0; farAwayUnit <= level; farAwayUnit++)
		{
			std::string currentPart = "";
			for (int16_t sideUnit = -farAwayUnit; sideUnit <= farAwayUnit; sideUnit++)
			{
				int16_t offsetX = farAwayUnit * directionX - sideUnit * directionY;
				int16_t offsetY = farAwayUnit * directionY + sideUnit * directionX;

				int16_t x = player->GetX() + offsetX;
				int16_t y = player->GetY() + offsetY;

				Tile tile = map->Get(x, y);

				if (tile.quantity > 0)
					currentPart += GetResourceTypeName(tile.type) + " ";

				for (size_t i = 0; i < players.size(); i++)
				{
					if (players[i]->GetSocketFd() == player->GetSocketFd())
						continue;

					if (players[i]->GetX() == x && players[i]->GetY() == y)
					{
						currentPart += "joueur ";
						break ;
					}
				}

				if (!currentPart.empty())
					currentPart.erase(currentPart.find_last_of(' '));

				if (sideUnit < level)
					currentPart += ", ";

				ss << currentPart;
				currentPart.clear();
			}
		}

		ss << "}";
		player->SendMessage(ss.str());
		return true;
	}

private:
	std::string GetResourceTypeName(int32_t type)
	{
		std::string resourceTypeNames[] = {
			"nourriture",
			"linemate",
			"deraumere",
			"sibur",
			"mendiane",
			"phiras",
			"thystame"
		};
		return resourceTypeNames[type];
	}
};
