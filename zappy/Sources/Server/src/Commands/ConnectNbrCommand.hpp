/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectNbrCommand.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:49:40 by acoezard          #+#    #+#             */
/*   Updated: 2024/04/22 09:11:10 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Command.hpp"
#include "Game/Game.hpp"
#include "Game/Client.hpp"
#include "Game/Team.hpp"

struct ConnectNbrCommand : public Command
{
	bool BeforeQueue(Game* game, Client* player, std::vector<std::string> args) override
	{
		(void) game;
		(void) args;
		return player->GetTeam() != nullptr;
	}

	bool AfterQueue(Game* game, Client* player, std::vector<std::string> args) override
	{
		(void) game;
		(void) args;

		Team* team = player->GetTeam();

		std::stringstream ss;
		ss << team->GetMaxPlayers() - team->GetPlayersCount();
		player->SendMessage(ss.str());

		return true;
	}
};
