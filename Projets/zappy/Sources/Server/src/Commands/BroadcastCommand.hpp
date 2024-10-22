/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BroadcastCommand.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:47:39 by acoezard          #+#    #+#             */
/*   Updated: 2024/04/29 09:59:45 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Command.hpp"
#include "Game/Game.hpp"
#include "Game/Client.hpp"
#include "Game/Map.hpp"
#include <cmath>

struct BroadcastCommand : public Command
{
	bool BeforeQueue(Game* game, Client* player, std::vector<std::string> args) override
	{
		(void) game;
		(void) player;
		return args.size() == 1;
	}

	bool AfterQueue(Game* game, Client* player, std::vector<std::string> args) override
	{
		int x = player->GetX();
		int y = player->GetY();
		for (Client *c: game->GetAllValidPlayers())
		{
			if (c->GetId() == player->GetId())
				continue;
			int k = 0;

			int target_x = c->GetX();
			int target_y = c->GetY();

			if (target_x != x || target_y != y)
			{
				int dx = abs(target_x - x);
				int dy = abs(target_y - y);

				bool up = target_y > y;
				bool left = target_x > x;

				if (dx > game->GetMap()->GetWidth() / 2)
				{
					dx = game->GetMap()->GetWidth() - dx;
					left = !left;
				}
				if (dy > game->GetMap()->GetHeight() / 2)
				{
					dy = game->GetMap()->GetHeight() - dy;
					up = !up;
				}

				double angle_direction = std::atan2(dy, dx);
				if (up && left)
					angle_direction = (90 * (M_PI / 180.0)) + (90 * (M_PI / 180.0) - angle_direction);
				else if (!up && left)
					angle_direction = 180 * (M_PI / 180.0) + angle_direction;
				else if (!up && !left)
					angle_direction = 270 * (M_PI / 180.0) + (90 * (M_PI / 180.0) - angle_direction);

				if (angle_direction * (180.0 / M_PI) == 360)
					angle_direction = 0;

				int orientation = c->GetOrientation();
				orientation = orientation == 1 ? 0 : orientation == 2 ? 270 : orientation == 3 ? 180 : 90;

				double angle_reception = angle_direction - orientation * (M_PI / 180.0);

				double angle = std::fmod((angle_reception * 180.0 / M_PI + 360), 360);

				if (angle == 45)
					k = 2;
				else if (angle == 135)
					k = 4;
				else if (angle == 225)
					k = 6;
				else if (angle == 315)
					k = 8;
				else if (angle > 315 || angle < 45)
					k = 1;
				else if (angle > 45 && angle < 135)
					k = 3;
				else if (angle > 135 && angle < 225)
					k = 5;
				else if (angle > 225 && angle < 315)
					k = 7;
			}

			c->SendMessage("message " + std::to_string(k) + "," + args[0]);

			game->SendMessageToGfx("pbc " + std::to_string(player->GetId()) + " " + args[0]);
		}
		player->SendMessage("ok");
		return true;
	}
};
