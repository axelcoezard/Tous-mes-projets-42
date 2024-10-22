/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GaucheCommand.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:34:59 by acoezard          #+#    #+#             */
/*   Updated: 2024/04/22 08:59:48 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Command.hpp"
#include "Game/Game.hpp"
#include "Game/Client.hpp"

struct GaucheCommand : public Command
{
	bool BeforeQueue(Game* game, Client* player, std::vector<std::string> args) override
	{
		(void) game;
		(void) player;
		return args.size() == 0;
	}

	bool AfterQueue(Game* game, Client* player, std::vector<std::string> args) override
	{
		(void) args;
		player->RotateLeft();
		player->SendMessage("ok");

		game->SendMessageToGfx("ppo " + std::to_string(player->GetId()) + " " +
			std::to_string(player->GetPosition(0)) + " " +
			std::to_string(player->GetPosition(1)) + " " +
			std::to_string(player->GetOrientation()));
		return true;
	}
};
