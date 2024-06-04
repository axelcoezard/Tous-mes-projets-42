/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ForkCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:49:09 by acoezard          #+#    #+#             */
/*   Updated: 2024/05/13 10:51:54 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Command.hpp"
#include "Game/Game.hpp"
#include "Game/Client.hpp"

struct ForkCommand : public Command
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

		if (player->GetTeam() == NULL || !player->GetTeam()->CanFork(player))
		{
			player->SendMessage("ko");
			return false;
		}

		int32_t index = game->AddEgg(player);

		player->SendMessage("ok");

		game->SendMessageToGfx("enw " + std::to_string(index)
			+ " " + std::to_string(player->GetId())
			+ " " + std::to_string(player->GetX())
			+ " " + std::to_string(player->GetY()));

		return true;
	}
};
