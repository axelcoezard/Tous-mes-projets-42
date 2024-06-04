/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrendCommand.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:46:00 by acoezard          #+#    #+#             */
/*   Updated: 2024/05/07 09:49:51 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Command.hpp"
#include "Game/Game.hpp"
#include "Game/Map.hpp"
#include "Game/Client.hpp"
#include <Tile.hpp>

struct PrendCommand : public Command
{
	bool BeforeQueue(Game* game, Client* player, std::vector<std::string> args) override
	{
		(void) game;
		(void) player;
		return args.size() == 1;
	}

	bool AfterQueue(Game* game, Client* player, std::vector<std::string> args) override
	{
		int32_t x = player->GetPosition(0);
		int32_t y = player->GetPosition(1);

		try
		{
			Tile &tile = game->GetMap()->PickResource(x, y, args[0]);
			int32_t resourceId = GetResourceTypeId(args[0]);

			if (resourceId == 0)
				player->IncreaseResource(resourceId, 126);
			else
				player->IncreaseResource(resourceId, 1);

			if (game->IsDebugMode())
			{
				Console::Log("Player " + std::to_string(player->GetId()) + " picked " + args[0]
					+ " at " + std::to_string(x) + ", " + std::to_string(y)
					+ " | Quantity left: " + std::to_string(tile.quantity)
					+ " | Player inventory: " + std::to_string(player->GetResource(resourceId)));
			}

			player->SendMessage("ok");

			game->SendMessageToGfx("bct " + game->GetMap()->SerializeTile(x, y));

			return true;
		}
		catch (std::out_of_range &e)
		{
			player->SendMessage("ko");
			return false;
		}
	}

private:
	int32_t GetResourceTypeId(std::string type)
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

		for (int32_t i = 0; i < RESSOURCES_COUNT; i++)
		{
			if (resourceTypeNames[i] == type)
				return i;
		}
		return -1;
	}
};
