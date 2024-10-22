/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:35:46 by acoezard          #+#    #+#             */
/*   Updated: 2024/05/13 10:50:42 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Map;
class Socket;
class Client;
class Team;
enum class ResourceType;

struct GameProperties
{
	int32_t mapWidth;
	int32_t mapHeight;
	int32_t tickRate;
};

struct Egg
{
	int32_t index;
	int32_t x;
	int32_t y;

	Team *team;
	Client *client;
	int32_t hatch_tick;
};

class Game
{
private:
	Map* m_Map;

	std::vector<Team*> m_Teams;
	std::vector<Client*> m_Players;
	std::vector<Egg*> m_Eggs;

	Client* m_pGraphicClient = nullptr;
	bool m_DebugMode = false;

	int32_t m_tickRate = TICK_RATE;
	int32_t m_ticks = 1;

	int32_t m_MaxClientsPerTeamAtBeginning = 10;

public:
	Game(GameProperties& gameProperties);
	~Game();

	void Initialize();

	bool Update();
	bool UpdateTeams();
	void UpdateEggs();
	void UpdatePlayers();

	Team* AddTeam(std::string name);
	Team* GetTeamByName(std::string name);
	Team* GetTeamByIndex(int32_t index);
	std::vector<Team*> GetAllTeams();
	int32_t GetTeamCount();

	Client* AddPlayer(Socket* socket);
	void RemovePlayer(Socket* player);

	int GetClientsCount();
	Client* GetPlayerBySocket(Socket* socket);
	std::vector<Client*> GetAllPlayers();
	std::vector<Client*> GetAllValidPlayers();
	std::vector<Client*> GetAllPlayersByTile(int32_t x, int32_t y);
	std::vector<Client*> GetAllPlayersByTileAndLevel(int32_t x, int32_t y, int32_t level);

	void SetMaxClientsPerTeamAtBeginning(int32_t maxClientsPerTeamAtBeginning);
	int32_t GetMaxClientsPerTeamAtBeginning();

	Client* GetGraphicClient();
	void SetGraphicClient(Client* client);

	void SendMessageToGfx(std::string message);

	int32_t GetTickRate() const;
	int32_t GetTicks() const;
	void IncTicks();

	int32_t AddEgg(Client* client);

	Map* GetMap();
	bool CheckMapResources();

	void SetDebugMode(bool debugMode);
	bool IsDebugMode();
};
