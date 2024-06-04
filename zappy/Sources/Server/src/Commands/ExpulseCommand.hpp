/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExpulseCommand.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:46:56 by acoezard          #+#    #+#             */
/*   Updated: 2024/04/22 10:05:03 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Command.hpp"
#include "Game/Game.hpp"
#include "Game/Client.hpp"

struct ExpulseCommand : public Command
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

		std::vector<Client*> players = game->GetAllPlayersByTile(player->GetX(), player->GetY());
		for (Client* p : players)
		{
			if (p->GetId() == player->GetId())
				continue;

			p->SetX(p->GetX() + player->GetDirectionX());
			p->SetY(p->GetY() + player->GetDirectionY());
			p->SendMessage("deplacement " + std::to_string(GetDirectionIndexFromOrientation(player->GetOrientation())));
		}

		player->SendMessage("ok");
		return true;
	}

private:
	int32_t GetDirectionIndexFromOrientation(int32_t fromOrientation)
	{
		if (fromOrientation == 1) // if come from East, reverse direction is West
			return 3;
		if (fromOrientation == 2) // if come from  South, reverse direction is North
			return 4;
		if (fromOrientation == 3) // if come from West, reverse direction is East
			return 1;
		if (fromOrientation == 4) // if come from North, reverse direction is South
			return 2;
		return 0;
	}
};
