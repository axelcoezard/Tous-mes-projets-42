/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EquipeCommand.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:55:58 by acoezard          #+#    #+#             */
/*   Updated: 2024/05/07 15:23:55 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Command.hpp"
#include "Game/Game.hpp"
#include "Game/Map.hpp"
#include "Game/Client.hpp"
#include "Game/Team.hpp"

struct EquipeCommand : public Command
{
	bool BeforeQueue(Game* game, Client* player, std::vector<std::string> args) override
	{
		(void) game;
		(void) player;
		return args.size() == 1;
	}

	bool AfterQueue(Game* game, Client* player, std::vector<std::string> args) override
	{
		std::stringstream mapSizeMessage;
		mapSizeMessage << game->GetMap()->GetWidth() << " " << game->GetMap()->GetHeight();

		Team* team = game->GetTeamByName(args[0]);
		if (team == NULL)
		{
			player->SendMessage(std::to_string(0).c_str());
			player->SendMessage(mapSizeMessage.str());
			return false;
		}

		if (team->GetPlayersCount() >= game->GetMaxClientsPerTeamAtBeginning()
			&& !team->HasNewBornCoordinates())
		{
			player->SendMessage(std::to_string(0).c_str());
			player->SendMessage(mapSizeMessage.str());
			return false;
		}

		const int availablePlayerCount = team->GetAvailablePlayersCount();

		player->SendMessage(std::to_string(availablePlayerCount).c_str());
		player->SendMessage(mapSizeMessage.str());

		if (availablePlayerCount == 0)
			return false;

		team->AddPlayer(game, player);

		player->SetConnected(true);

		game->SendMessageToGfx("pnw " + std::to_string(player->GetId()) + " " +
			std::to_string(player->GetPosition(0)) + " " +
			std::to_string(player->GetPosition(1)) + " " +
			std::to_string(player->GetOrientation()) + " " +
			std::to_string(player->GetLevel()) + " " +
			player->GetTeam()->GetName());

		return true;
	}
};
