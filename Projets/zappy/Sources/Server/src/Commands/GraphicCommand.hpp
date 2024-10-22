/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicCommand.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:21:57 by acoezard          #+#    #+#             */
/*   Updated: 2024/06/04 10:07:01 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Command.hpp"
#include "Game/Game.hpp"
#include "Game/Team.hpp"
#include "Game/Map.hpp"
#include "Game/Client.hpp"

#include <ResourceType.hpp>
#include <Tile.hpp>

struct GraphicCommand : public Command
{
	bool BeforeQueue(Game* game, Client* client, std::vector<std::string> args) override
	{
		(void) game;
		(void) client;
		(void) args;
		return true;
	}

	bool AfterQueue(Game* game, Client* client, std::vector<std::string> args) override
	{
		(void) args;

		client->SetType(ClientType::GRAPHIC);

		game->SetGraphicClient(client);

		int32_t tick_rate = game->GetTickRate();
		client->SendMessage("sgt " + std::to_string(tick_rate));

		Console::Log("Sending map to graphic client...");
		if (game->GetMap() != nullptr)
		{
			int32_t mapWidth = game->GetMap()->GetWidth();
			int32_t mapHeight = game->GetMap()->GetHeight();

			client->SendMessage("msz " + std::to_string(mapWidth) + " " + std::to_string(mapHeight));

			for (int32_t i = 0; i < mapWidth * mapHeight; ++i)
			{
				client->SendMessage("bct " + game->GetMap()->SerializeTile(i % mapWidth, i / mapWidth));
			}
		}
		Console::Log(" => Map received by graphic client");

		int32_t nbTeams = game->GetTeamCount();
		for (int32_t i = 0; i < nbTeams; ++i)
		{
			Team* team = game->GetTeamByIndex(i);
			if (team == nullptr)
				continue;

			client->SendMessage("tna " + team->GetName() + " " + std::to_string(team->GetMaxLevel()));
		}

		std::vector<Client*> clients = game->GetAllValidPlayers();
		for (size_t i = 0; i < clients.size(); i++)
		{
			if (clients[i] == nullptr)
				continue;

			std::string teamName = clients[i]->GetTeam() == nullptr ? "" : clients[i]->GetTeam()->GetName();

			game->SendMessageToGfx("pnw " + std::to_string(clients[i]->GetId()) + " " +
				std::to_string(clients[i]->GetPosition(0)) + " " +
				std::to_string(clients[i]->GetPosition(1)) + " " +
				std::to_string(clients[i]->GetOrientation()) + " " +
				std::to_string(clients[i]->GetLevel()) + " " + teamName);
		}

		return true;
	}
};
