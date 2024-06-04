/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PoseCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:46:37 by acoezard          #+#    #+#             */
/*   Updated: 2024/04/22 09:36:42 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Command.hpp"
#include "Game/Game.hpp"
#include "Game/Map.hpp"
#include "Game/Client.hpp"
#include <Tile.hpp>

struct PoseCommand : public Command
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

		int32_t resourceCount = player->GetResource(GetResourceTypeId(args[0]));
		if (resourceCount == 0)
		{
			player->SendMessage("ko");
			return false;
		}

		game->GetMap()->SetResource(x, y, GetResourceTypeId(args[0]), 1);
		player->SetResource(GetResourceTypeId(args[0]), resourceCount - 1);
		player->SendMessage("ok");

		game->SendMessageToGfx("bct " + game->GetMap()->SerializeTile(x, y));

		return true;
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
