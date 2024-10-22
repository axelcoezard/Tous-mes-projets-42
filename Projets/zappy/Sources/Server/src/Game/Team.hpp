/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Team.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:51:20 by acoezard          #+#    #+#             */
/*   Updated: 2024/06/04 10:05:39 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Client;
class Game;

class Team
{
private:
	std::string m_Name;

	std::vector<Client*> m_Players;
	std::vector<Client*> m_AvailablePlayers;

	int32_t m_MaxPlayers;

	std::vector<std::tuple<int, int, int>> m_newBornCoordinates;

	Client* forkingClient = nullptr;

	uint32_t maxLevel = 0;

public:
	Team(std::string name, int32_t maxPlayers);
	~Team();

	std::string GetName() const;

	void AddPlayer(Game* game, Client* player);
	void RemovePlayer(Client* player);

	int32_t GetMaxPlayers() const;
	int32_t GetPlayersCount() const;
	int32_t GetAvailablePlayersCount() const;
	int32_t GetMinPlayerLevels() const;
	int32_t GetMaxPlayerLevels() const;
	int32_t GetAveragePlayers() const;
	bool	 IsFull() const;
	bool	 IsEmpty() const;
	bool	 AllPlayersThatAreAtLevelOrMore(int32_t level) const;

	void	SetMaxLevel(uint32_t level);
	uint32_t GetMaxLevel() const;

	void	 AddNewBornCoordinates(int x, int y, int id);
	bool	 HasNewBornCoordinates();

	void	 SetForkingClient(Client* client);
	bool 	 CanFork(Client* client);
};
