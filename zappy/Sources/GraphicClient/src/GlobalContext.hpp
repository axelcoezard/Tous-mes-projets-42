/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlobalContext.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:04:04 by acoezard          #+#    #+#             */
/*   Updated: 2024/06/03 21:26:46 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Tile.hpp>

struct PlayerContext
{
	int32_t id;
	int32_t x;
	int32_t y;

	int32_t orientation;

	int32_t level;
	std::string team;
	int32_t inventory[7];

	bool selected = false;
};

struct EggContext
{
	int32_t id;
	int32_t playerId;
	int32_t x;
	int32_t y;
	int32_t hasHatched;
};

struct TeamContext
{
	std::string name;
	int32_t averageLevel;
	int32_t maxLevel;
};

struct SoundContext
{
	int32_t fromId;
	int32_t fromX;
	int32_t fromY;
	int32_t tickElapsed;
	std::string message;
};

struct GlobalContext
{
	bool appRunning = false;

	bool hasMapSize = false;
	int32_t width = 1;
	int32_t height = 1;
	Tile* map = nullptr;

	bool hasTeams = false;
	int32_t teamCount;
	std::vector<TeamContext> teams;

	bool hasWinner = false;
	std::string winner;

	bool hasGameOver = false;

	bool hasPlayers = false;
	int32_t playerCount;
	int32_t playerDeadCount;
	std::vector<PlayerContext> players;
	int followedUserId;

	bool hasEggs = false;
	int32_t eggCount;
	std::vector<EggContext> eggs;

	bool hasSounds = false;
	int32_t soundCount;
	std::vector<SoundContext> sounds;

	bool hasTickRate = false;
	int32_t tickRate;
};
