/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InventaireCommand.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:44:47 by acoezard          #+#    #+#             */
/*   Updated: 2024/04/22 09:02:39 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Command.hpp"
#include "Game/Game.hpp"
#include "Game/Client.hpp"

struct InventaireCommand : public Command
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
		(void) game;
		(void) args;

		std::stringstream ss;
		ss << "{";
		ss << "nourriture " << player->GetResource(0) << ", ";
		ss << "linemate " << player->GetResource(1) << ", ";
		ss << "deraumere " << player->GetResource(2) << ", ";
		ss << "sibur " << player->GetResource(3) << ", ";
		ss << "mendiane " << player->GetResource(4) << ", ";
		ss << "phiras " << player->GetResource(5) << ", ";
		ss << "thystame " << player->GetResource(6) << "";
		ss << "}";

		player->SendMessage(ss.str());
		return true;
	}
};
