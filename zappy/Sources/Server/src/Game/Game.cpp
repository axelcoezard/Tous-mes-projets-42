/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:35:39 by acoezard          #+#    #+#             */
/*   Updated: 2024/06/04 10:09:24 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Network/Socket.hpp>

#include "Game.hpp"

#include "Map.hpp"
#include "Client.hpp"
#include "Team.hpp"

#include <ResourceType.hpp>
#include <Tile.hpp>

Game::Game(GameProperties& gameProperties)
{
	m_tickRate = gameProperties.tickRate;
	m_Map = new Map(gameProperties.mapWidth, gameProperties.mapHeight);
}

Game::~Game()
{
	for (size_t i = 0; i < m_Players.size(); ++i)
		delete m_Players[i];

	delete m_Map;
}

void Game::Initialize()
{
	m_Map->Initialize();
	while (!CheckMapResources())
		m_Map->Initialize();
}

bool Game::CheckMapResources() {
	if (m_Map == NULL)
		return false;
	int32_t resources[RESSOURCES_COUNT];
	for (int32_t i = 0; i < RESSOURCES_COUNT; i++)
		resources[i] = m_Map->GetRessourceCount(i);
	if (resources[1] < (int)(21 * m_Teams.size()))
		return false;
	if (resources[2] < (int)(11.5 * m_Teams.size()))
		return false;
	if (resources[3] < (int)(15.5 * m_Teams.size()))
		return false;
	if (resources[4] < (int)(6.5 * m_Teams.size()))
		return false;
	if (resources[5] < (int)(10.5 * m_Teams.size()))
		return false;
	if (resources[6] < (int)(1 * m_Teams.size()))
		return false;
	return true;
}

bool Game::Update()
{
	if (!UpdateTeams())
		return false;

	UpdateEggs();
	UpdatePlayers();

	m_Map->Update();
	return true;
}

bool Game::UpdateTeams()
{
	for (Team* team : m_Teams)
	{
		if (team->GetPlayersCount() == 0)
			continue ;

		uint32_t averageLevel = team->GetAveragePlayers();
		if (averageLevel > team->GetMaxLevel())
			team->SetMaxLevel(averageLevel);

		// If a team is level 8 and full, it wins, then we send a message to the graphic client
		if (team->IsFull() && team->GetMaxLevel() >= 8)
		{
			SendMessageToGfx("seg " + team->GetName());
			return false;
		}
	}
	return true;
}

void Game::UpdateEggs()
{
	for (Egg* egg : m_Eggs)
	{
		if (m_ticks >= egg->hatch_tick)
		{
			egg->team->AddNewBornCoordinates(egg->x, egg->y, egg->index);
			m_Eggs.erase(std::remove(m_Eggs.begin(), m_Eggs.end(), egg), m_Eggs.end());
			SendMessageToGfx("eht " + std::to_string(egg->index));

			if (IsDebugMode())
				Console::Log("Egg hatched at " + std::to_string(egg->x) + " " + std::to_string(egg->y) + " for team " + egg->team->GetName());

			if (egg->team != NULL)
				egg->team->SetForkingClient(nullptr);
		}
	}
}

void Game::UpdatePlayers()
{
	for (Client* player : m_Players)
	{
		if (player->IsConnected() == false)
			continue ;

		if (player->GetType() == ClientType::PLAYER)
		{
			if (player->GetHealth() > 0 && player->HasTeam())
				player->DecreaseHealth(1);

			if (player->GetHealth() <= 0)
			{
				SendMessageToGfx("pdi " + std::to_string(player->GetId()));

				player->SetConnected(false);
				player->GetTeam()->RemovePlayer(player);
				player->SetTeam(NULL);
				player->SendMessage("mort");
			}
		}
	}
}

Team* Game::AddTeam(std::string name)
{
	Team* team = new Team(name, 6);
	m_Teams.push_back(team);
	return team;
}

Team* Game::GetTeamByName(std::string name)
{
	for (size_t i = 0; i < m_Teams.size(); ++i)
	{
		if (m_Teams[i] != NULL && m_Teams[i]->GetName() == name)
			return m_Teams[i];
	}
	return NULL;
}

Team* Game::GetTeamByIndex(int32_t index)
{
	if (static_cast<size_t>(index) >= m_Teams.size())
		return NULL;
	return m_Teams[index];
}

std::vector<Team*> Game::GetAllTeams()
{
	return m_Teams;
}

int32_t Game::GetTeamCount()
{
	return m_Teams.size();
}

Client* Game::AddPlayer(Socket* socket)
{
	Client* player = new Client(m_Players.size(), socket->m_Instance, this);
	player->SetPosition(0, (int) (((float) rand() / (float) RAND_MAX) * m_Map->GetWidth()));
	player->SetPosition(1, (int) (((float) rand() / (float) RAND_MAX) * m_Map->GetHeight()));
	m_Players.push_back(player);
	return player;
}

void Game::RemovePlayer(Socket* socket)
{
	for (size_t i = 0; i < m_Players.size(); ++i)
	{
		auto& player = m_Players[i];
		if (player->GetSocketFd() == socket->m_Instance)
		{
			m_Players.erase(m_Players.begin() + i);
			delete player;
			break;
		}
	}
}

Client* Game::GetPlayerBySocket(Socket* socket)
{
	for (size_t i = 0; i < m_Players.size(); ++i)
	{
		if (m_Players[i]->GetSocketFd() == socket->m_Instance)
			return m_Players[i];
	}
	return nullptr;
}


Client* Game::GetGraphicClient()
{
	return m_pGraphicClient;
}

void Game::SetGraphicClient(Client* client)
{
	m_pGraphicClient = client;
}

void Game::SendMessageToGfx(std::string message)
{
	if (m_pGraphicClient != nullptr)
		m_pGraphicClient->SendMessage(message);
}


Map* Game::GetMap()
{
	return m_Map;
}

int Game::GetClientsCount()
{
	return m_Players.size() + (m_pGraphicClient != nullptr ? 1 : 0);
}

std::vector<Client*> Game::GetAllPlayers()
{
	return m_Players;
}

std::vector<Client*> Game::GetAllValidPlayers()
{
	std::vector<Client*> players;

	for (Client* player : m_Players)
	{
		if (player->IsConnected() // the player client must be connected to server
			&& player->GetType() == ClientType::PLAYER // the player must be a player
			&& player->HasTeam()) // the player must have a team to play
			players.push_back(player);
	}
	return players;
}

std::vector<Client*> Game::GetAllPlayersByTile(int32_t x, int32_t y)
{
	std::vector<Client*> players;

	for (Client* player : m_Players)
	{
		if (!player->IsConnected() || player->GetType() != ClientType::PLAYER || !player->HasTeam())
			continue;

		if (player->GetPosition(0) == x && player->GetPosition(1) == y)
			players.push_back(player);
	}
	return players;
}

std::vector<Client*> Game::GetAllPlayersByTileAndLevel(int32_t x, int32_t y, int32_t level)
{
	std::vector<Client*> players;

	for (Client* player : m_Players)
	{
		if (!player->IsConnected() || player->GetType() != ClientType::PLAYER || !player->HasTeam())
			continue;

		if (player->GetPosition(0) == x && player->GetPosition(1) == y && player->GetLevel() >= level)
			players.push_back(player);
	}
	return players;
}

int32_t Game::GetTickRate() const
{
	return m_tickRate;
}

int32_t Game::GetTicks() const
{
	return m_ticks;
}

void Game::IncTicks()
{
	m_ticks++;
}

int32_t Game::AddEgg(Client* client)
{
	Egg* egg = new Egg();
	egg->index = m_Eggs.size();
	egg->x = client->GetPosition(0);
	egg->y = client->GetPosition(1);
	egg->team = client->GetTeam();
	egg->client = client;
	egg->hatch_tick = m_ticks + 600;

	if (client->GetTeam() != nullptr)
		client->GetTeam()->SetForkingClient(client);

	m_Eggs.push_back(egg);
	return egg->index;
}

void Game::SetDebugMode(bool debugMode)
{
	m_DebugMode = debugMode;
}

bool Game::IsDebugMode()
{
	return m_DebugMode;
}

void Game::SetMaxClientsPerTeamAtBeginning(int32_t maxClientsPerTeamAtBeginning)
{
	m_MaxClientsPerTeamAtBeginning = maxClientsPerTeamAtBeginning;
}

int32_t Game::GetMaxClientsPerTeamAtBeginning()
{
	return m_MaxClientsPerTeamAtBeginning;
}
