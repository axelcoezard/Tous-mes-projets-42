/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IncantationCommand.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:48:28 by acoezard          #+#    #+#             */
/*   Updated: 2024/06/04 10:01:08 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Command.hpp"
#include "Game/Game.hpp"
#include "Game/Client.hpp"
#include "Game/Team.hpp"

struct Ritual
{
	int32_t fromLevel;
	int32_t toLevel;

	int32_t playersCount;

	union
	{
		struct {
			int32_t linemate;
			int32_t deraumere;
			int32_t sibur;
			int32_t mendiane;
			int32_t phiras;
			int32_t thystame;
		};
		int32_t resources[6];
	};
};

struct IncantationCommand : public Command
{
	Ritual m_Rituals[8] = {
		{ 1, 2, 1, {{ 1, 0, 0, 0, 0, 0 }} },
		{ 2, 3, 2, {{ 1, 1, 1, 0, 0, 0 }} },
		{ 3, 4, 2, {{ 2, 0, 1, 0, 2, 0 }} },
		{ 4, 5, 4, {{ 1, 1, 2, 0, 1, 0 }} },
		{ 5, 6, 4, {{ 1, 2, 1, 3, 0, 0 }} },
		{ 6, 7, 6, {{ 1, 2, 3, 0, 1, 0 }} },
		{ 7, 8, 6, {{ 2, 2, 2, 2, 2, 1 }} }
	};

	// On verifie si le joueur peut lancer le rituel et si oui on le met en file d'attente
	bool BeforeQueue(Game* game, Client* player, std::vector<std::string> args) override
	{
		(void) args;

		if (player->GetLevel() < 1)
			return false;

		// On recupere les regles du rituel pour passer du niveau n au niveau n+1
		Ritual ritual = m_Rituals[player->GetLevel() - 1];

		// On recupere tous les joueurs qui sont sur la case du joueur et qui sont du meme niveau
		std::vector<Client*> players = game->GetAllPlayersByTileAndLevel(player->GetX(), player->GetY(), player->GetLevel());

		// Si le nombre de joueurs est inferieur au nombre de joueurs requis pour le rituel on ne continue pas
		// Si les ressources des joueurs ne correspondent pas aux ressources requises pour le rituel on ne continue pas
		if (players.size() < static_cast<size_t>(ritual.playersCount) || !AllPlayersHaveResourcesTogether(players, &ritual))
			return false;

		for (int i = 0; i < 6; i++)
			player->DecreaseResource(i + 1, ritual.resources[i]);

		// On previent le client qu'on lance l'incantation
		player->SendMessage("elevation en cours");

		// On previent le client graphique qu'on lance l'incantation
		{
			std::stringstream ss;
			ss << "pic " << player->GetX() << " " << player->GetY() << " " << player->GetLevel();
			for (auto p : players) ss << " " << p->GetId();
			game->SendMessageToGfx(ss.str());
		}
		return true;
	}

	// 300 ticks plus tard on augmente le niveau de tous les joueurs sur la case
	bool AfterQueue(Game* game, Client* player, std::vector<std::string> args) override
	{
		(void) args;

		std::vector<Client*> players = game->GetAllPlayersByTileAndLevel(player->GetX(), player->GetY(), player->GetLevel());

		// On previent le client graphique qu'on a termine l'incantation
		game->SendMessageToGfx("pie " + std::to_string(player->GetX()) + " " + std::to_string(player->GetY()) + " 1");

		// On annonce les niveaux des joueurs
		for (auto p : players)
		{
			p->IncreaseLevel();
			p->SendMessage("niveau actuel: " + std::to_string(p->GetLevel()));
			game->SendMessageToGfx("plv " + std::to_string(p->GetId()) + " " + std::to_string(p->GetLevel()));
		}

		return true;
	}

	bool AllPlayersHaveResourcesTogether(std::vector<Client*> players, Ritual* ritual)
	{
		for (int32_t i = 1; i < 7; i++)
		{
			int32_t count = 0;

			for (auto player : players)
				count += player->GetResource(i);

			if (count < ritual->resources[i - 1])
				return false;
		}
		return true;
	}
};
