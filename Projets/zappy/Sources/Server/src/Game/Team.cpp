/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Team.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:51:01 by acoezard          #+#    #+#             */
/*   Updated: 2024/06/04 10:10:12 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Team.hpp"
#include "Client.hpp"
#include "Game.hpp"

Team::Team(std::string name, int32_t maxPlayers)
{
	m_Name = name;
	m_MaxPlayers = maxPlayers;
	maxLevel = 0;
}

Team::~Team()
{
	m_Players.clear();
	m_newBornCoordinates.clear();
}

std::string Team::GetName() const
{
	return m_Name;
}

void Team::AddPlayer(Game* game, Client* player)
{

	// If the player is an egg, we set its position to the first new born coordinates
	if (m_newBornCoordinates.size() > 0)
	{
		player->SetPosition(0, std::get<0>(m_newBornCoordinates[0]));
		player->SetPosition(1, std::get<1>(m_newBornCoordinates[0]));
		player->SetIsEgg(true);

		game->SendMessageToGfx("ebo " + std::to_string(std::get<2>(m_newBornCoordinates[0])));

		m_newBornCoordinates.erase(m_newBornCoordinates.begin());
	}

	// Then, we add the player to the team
	m_Players.push_back(player);

	player->SetTeam(this);
}

void Team::RemovePlayer(Client* player)
{
	for (auto it = m_Players.begin(); it != m_Players.end(); it++)
	{
		if ((*it)->GetSocketFd() == player->GetSocketFd())
		{
			m_Players.erase(it);
			break;
		}
	}
}

int32_t Team::GetMaxPlayers() const
{
	return m_MaxPlayers;
}

int32_t Team::GetPlayersCount() const
{
	return m_Players.size();
}

int32_t Team::GetAvailablePlayersCount() const
{
	return m_MaxPlayers - m_Players.size();
}

int32_t Team::GetMinPlayerLevels() const
{
	int32_t min = 0;

	for (auto player : m_Players)
	{
		if (min == 0 || player->GetLevel() < min)
			min = player->GetLevel();
	}
	return min;
}

int32_t Team::GetMaxPlayerLevels() const
{
	int32_t max = 0;

	for (auto player : m_Players)
	{
		if (player->GetLevel() > max)
			max = player->GetLevel();
	}
	return max;
}

int32_t Team::GetAveragePlayers() const
{
	int32_t sum = 0;

	for (auto player : m_Players)
	{
		sum += player->GetLevel();
	}
	return sum / m_Players.size();
}

bool Team::IsFull() const
{
	return m_Players.size() >= static_cast<size_t>(m_MaxPlayers);
}

bool Team::IsEmpty() const
{
	return m_Players.size() == 0;
}

bool Team::AllPlayersThatAreAtLevelOrMore(int32_t level) const
{
	for (auto player : m_Players)
	{
		if (player->GetLevel() < level)
			return false;
	}
	return true;
}

void Team::AddNewBornCoordinates(int x, int y, int id)
{
	m_newBornCoordinates.push_back(std::make_tuple(x, y, id));
}

bool Team::HasNewBornCoordinates()
{
	return m_newBornCoordinates.size() > 0;
}

void Team::SetForkingClient(Client* client)
{
	forkingClient = client;
}

bool Team::CanFork(Client* client)
{
	if (client == nullptr)
		return false;

	if (client->GetTeam() == nullptr)
		return false;

	if (client->GetTeam()->forkingClient == nullptr)
		return true;

	return client->GetTeam()->forkingClient->GetId() == client->GetId();
}

void Team::SetMaxLevel(uint32_t level)
{
	maxLevel = level;
}

uint32_t Team::GetMaxLevel() const
{
	return maxLevel;
}
