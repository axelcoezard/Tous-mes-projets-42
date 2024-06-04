/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketThread.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:31:52 by acoezard          #+#    #+#             */
/*   Updated: 2024/06/04 10:13:18 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Utils.hpp>
#include <Console.hpp>
#include <Tile.hpp>
#include <ResourceType.hpp>

#include "SocketThread.hpp"
#include "Network/Socket.hpp"
#include "GlobalContext.hpp"

SocketThread::SocketThread(GlobalContext* data, std::string hostname, int32_t port) : Thread(data)
{
	m_Hostname = hostname;
	m_Port = port;
}

SocketThread::~SocketThread()
{
	m_GlobalContext->appRunning = false;
}

void SocketThread::Update()
{
	m_Socket = new Socket(m_Port, m_Hostname);
	m_Socket->SetOption(SOCKET_REUSE_ADRESS, 1);

	if (!m_Socket->Connect()) {
		std::cout << strerror(errno) << std::endl;
		throw std::runtime_error("Failed to connect to server.");
	}

	while (m_GlobalContext->appRunning)
	{
		char tmpBuffer[1025];
		std::memset(tmpBuffer, 0, 1025);

		if (m_Socket->Receive(tmpBuffer, 1024) <= 0)
		{
			m_GlobalContext->appRunning = false;
			break;
		}

		if (std::string(tmpBuffer).empty())
			continue;

		m_Buffer += std::string(tmpBuffer);

		if (std::string(tmpBuffer)[std::string(tmpBuffer).size() - 1] != '\n')
			continue;

		if (m_Buffer.empty())
			m_Buffer = std::string(tmpBuffer);

		for (std::string& line : Utils::str_split(m_Buffer, "\n"))
		{
			if (line.empty())
				continue;
			ParseBufferLine(line);
		}
		m_Buffer.clear();
	}

	delete m_Socket;
}

void SocketThread::ParseBufferLine(std::string line)
{
	const char* tmpBuffer = line.c_str();
	std::vector<std::string> args = Utils::str_split(tmpBuffer, " ");

	if (std::strncmp(tmpBuffer, "BIENVENUE", 9) == 0)
	{
		const char* graphicType = "GRAPHIC\n";
		m_Socket->Send(graphicType, strlen(graphicType));
	}
	else if (std::strncmp(tmpBuffer, "msz", 3) == 0&& args.size() == 3) // map size
	{
		m_GlobalContext->width = atoi(args[1].c_str());
		m_GlobalContext->height = atoi(args[2].c_str());

		m_GlobalContext->map = new Tile[m_GlobalContext->width * m_GlobalContext->height];
		std::memset((void *)m_GlobalContext->map, 0, sizeof(Tile) * m_GlobalContext->width * m_GlobalContext->height);

		m_GlobalContext->hasMapSize = true;
	}
	else if (std::strncmp(tmpBuffer, "sgt", 3) == 0 && args.size() == 2) // tick rate
	{
		m_GlobalContext->tickRate = atoi(args[1].c_str());
		m_GlobalContext->hasTickRate = true;
	}
	else if (std::strncmp(tmpBuffer, "tna", 3) == 0 && args.size() == 3) // team names
	{
		m_GlobalContext->teams.push_back({
				.name = args[1],
				.averageLevel = 0,
				.maxLevel = std::atoi(args[2].c_str())
			});
		m_GlobalContext->teamCount += 1;
		m_GlobalContext->hasTeams = true;
	}
	else if (std::strncmp(tmpBuffer, "bct", 3) == 0 && args.size() >= 10) // tile content
	{
		int32_t x = atoi(args[1].c_str());
		int32_t y = atoi(args[2].c_str());
		int32_t index = x + y * m_GlobalContext->width;

		auto [resourceType, resourceQuantity] = GetTypeFromBctLine(args);

		m_GlobalContext->map[index].x = x;
		m_GlobalContext->map[index].y = y;
		m_GlobalContext->map[index].type = resourceType;
		m_GlobalContext->map[index].quantity = resourceQuantity;
		m_GlobalContext->map[index].dirty = true;
	}
	else if (std::strncmp(tmpBuffer, "pnw", 3) == 0 && args.size() == 7)
	{
		m_GlobalContext->players.push_back((PlayerContext) {
			.id = std::atoi(args[1].c_str()),
			.x = std::atoi(args[2].c_str()),
			.y = std::atoi(args[3].c_str()),
			.orientation = std::atoi(args[4].c_str()),
			.level = std::atoi(args[5].c_str()),
			.team = args[6],
			.inventory = {0, 0, 0, 0, 0, 0, 0},
			.selected = false
		});

		std::cout << "Player " << atoi(args[1].c_str()) << " joined the game." << std::endl;

		m_GlobalContext->playerCount++;
	}
	else if (std::strncmp(tmpBuffer, "ppo", 3) == 0 && args.size() == 5)
	{
		int32_t id = atoi(args[1].c_str());
		int32_t x = atoi(args[2].c_str());
		int32_t y = atoi(args[3].c_str());
		int32_t orientation = atoi(args[4].c_str());

		for (int32_t i = 0; i < m_GlobalContext->playerCount; i++)
		{
			if (m_GlobalContext->players[i].id == id)
			{
				m_GlobalContext->players[i].x = x;
				m_GlobalContext->players[i].y = y;
				m_GlobalContext->players[i].orientation = orientation;
				break;
			}
		}
	}
	else if (std::strncmp(tmpBuffer, "pin", 3) == 0 && args.size() == 11)
	{
		int32_t id = atoi(args[1].c_str());
		for (int32_t i = 0; i < m_GlobalContext->playerCount; i++)
		{
			if (m_GlobalContext->players[i].id == id)
			{
				m_GlobalContext->players[i].x = atoi(args[2].c_str());
				m_GlobalContext->players[i].y = atoi(args[3].c_str());
				m_GlobalContext->players[i].inventory[0] = atoi(args[4].c_str());
				m_GlobalContext->players[i].inventory[1] = atoi(args[5].c_str());
				m_GlobalContext->players[i].inventory[2] = atoi(args[6].c_str());
				m_GlobalContext->players[i].inventory[3] = atoi(args[7].c_str());
				m_GlobalContext->players[i].inventory[4] = atoi(args[8].c_str());
				m_GlobalContext->players[i].inventory[5] = atoi(args[9].c_str());
				m_GlobalContext->players[i].inventory[6] = atoi(args[10].c_str());
				break;
			}
		}
	}
	else if (std::strncmp(tmpBuffer, "seg", 3) == 0 && args.size() == 2)
	{
		m_GlobalContext->hasWinner = true;
		m_GlobalContext->hasGameOver = true;
		m_GlobalContext->winner = args[1];
	}
	else if (std::strncmp(tmpBuffer, "enw", 3) == 0 && args.size() == 5)
	{
		m_GlobalContext->eggs.push_back((EggContext) {
			.id = std::atoi(args[1].c_str()),
			.playerId = std::atoi(args[2].c_str()),
			.x = std::atoi(args[3].c_str()),
			.y = std::atoi(args[4].c_str()),
			.hasHatched = false
		});

		m_GlobalContext->eggCount++;
		m_GlobalContext->hasEggs = true;
	}
	else if (std::strncmp(tmpBuffer, "eht", 3) == 0 && args.size() == 2)
	{
		int32_t id = std::atoi(args[1].c_str());
		for (int32_t i = 0; i < m_GlobalContext->eggCount; i++)
		{
			if (m_GlobalContext->eggs[i].id == id)
			{
				m_GlobalContext->eggs[i].hasHatched = true;
				break;
			}
		}
	}
	else if (std::strncmp(tmpBuffer, "pdi", 3) == 0 && args.size( ) == 2)
	{
		int32_t id = std::atoi(args[1].c_str());
		for (int32_t i = 0; i < m_GlobalContext->playerCount; i++)
		{
			if (m_GlobalContext->players[i].id == id)
			{
				m_GlobalContext->players.erase(m_GlobalContext->players.begin() + i);
				m_GlobalContext->playerCount--;
				m_GlobalContext->playerDeadCount++;
				break;
			}
		}

		m_GlobalContext->hasGameOver = m_GlobalContext->playerCount + m_GlobalContext->eggCount == 0;
	}
	else if ((std::strncmp(tmpBuffer, "ebo", 3) == 0 || std::strncmp(tmpBuffer, "edi", 3) == 0) && args.size() == 2)
	{
		int32_t id = std::atoi(args[1].c_str());
		for (int32_t i = 0; i < m_GlobalContext->eggCount; i++)
		{
			if (m_GlobalContext->eggs[i].id == id)
			{
				m_GlobalContext->eggs.erase(m_GlobalContext->eggs.begin() + i);
				m_GlobalContext->eggCount--;
				break;
			}
		}
	}
	else if (std::strncmp(tmpBuffer, "pbc", 3) == 0 && args.size() == 3)
	{
		int32_t id = std::atoi(args[1].c_str());

		for (int32_t i = 0; i < m_GlobalContext->playerCount; i++)
		{
			if (m_GlobalContext->players[i].id == id)
			{
				m_GlobalContext->sounds.push_back((SoundContext) {
					.fromId = m_GlobalContext->players[i].id,
					.fromX = m_GlobalContext->players[i].x,
					.fromY = m_GlobalContext->players[i].y,
					.tickElapsed = 0,
					.message = std::string(args[2].c_str())
				});
				m_GlobalContext->hasSounds = true;
				m_GlobalContext->soundCount++;
				break;
			}
		}
	}
	else if (std::strncmp(tmpBuffer, "plv", 3) == 0)
	{
		int32_t id = std::atoi(args[1].c_str());
		int32_t level = std::atoi(args[2].c_str());

		for (int32_t i = 0; i < m_GlobalContext->playerCount; i++)
		{
			if (m_GlobalContext->players[i].id == id)
			{
				m_GlobalContext->players[i].level = level;
				break;
			}
		}
	}
}

std::pair<int16_t, int16_t> SocketThread::GetTypeFromBctLine(std::vector<std::string> args)
{
	if (std::atoi(args[3].c_str()) > 0)
		return {static_cast<int32_t>(ResourceType::Nourriture), std::atoi(args[3].c_str())};
	if (std::atoi(args[4].c_str()) > 0)
		return {static_cast<int32_t>(ResourceType::Linemate), std::atoi(args[4].c_str())};
	if (std::atoi(args[5].c_str()) > 0)
		return {static_cast<int32_t>(ResourceType::Deraumere), std::atoi(args[5].c_str())};
	if (std::atoi(args[6].c_str()) > 0)
		return {static_cast<int32_t>(ResourceType::Sibur), std::atoi(args[6].c_str())};
	if (std::atoi(args[7].c_str()) > 0)
		return {static_cast<int32_t>(ResourceType::Mendiane), std::atoi(args[7].c_str())};
	if (std::atoi(args[8].c_str()) > 0)
		return {static_cast<int32_t>(ResourceType::Phiras), std::atoi(args[8].c_str())};
	if (std::atoi(args[9].c_str()) > 0)
		return {static_cast<int32_t>(ResourceType::Thystame), std::atoi(args[9].c_str())};
	return {-1, 0};
}

std::thread* SocketThread::GetThread()
{
	return new std::thread(&SocketThread::Update, this);
}
