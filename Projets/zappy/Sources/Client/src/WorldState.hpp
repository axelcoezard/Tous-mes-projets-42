/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WorldState.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:10:42 by acoezard          #+#    #+#             */
/*   Updated: 2024/04/22 10:53:33 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Pathfinding.hpp"
#include "LevelGrid.hpp"
class WorldState
{
private:
	std::vector<std::vector<std::string>> m_Map;
	std::map<std::string, int32_t> m_Inventory;

	int m_Level = 1;
	int m_NbPlayer = 1;
	int m_NbPlayerReady = 1;
	int m_IncantationDirection = -1;
	std::string m_IdMaster = "";
	int m_Result = -1;
public:
	WorldState()
	{
		m_Map = std::vector<std::vector<std::string>>();
		m_Inventory = std::map<std::string, int32_t>();
	}

	~WorldState()
	{
		m_Map.clear();
		m_Inventory.clear();
	}

	void SetResult(int result)
	{
		m_Result = result;
	}

	void ResetNbPlayerReady()
	{
		m_NbPlayerReady = 1;
	}

	int GetResult()
	{
		return m_Result;
	}
	void SetIdMaster(std::string id)
	{
		id.erase(std::remove(id.begin(), id.end(), '\n'), id.end());
		m_IdMaster = id;
	}

	std::string GetIdMaster()
	{
		return m_IdMaster;
	}

	void IncNbPlayer()
	{
		m_NbPlayer++;
	}

	void IncLevel()
	{
		m_Level++;
	}

	void ResetNbPlayer()
	{
		m_NbPlayer = 1;
	}

	void ParseMap(std::string response)
	{
		std::cout << "parse" << std::endl;
		response = Utils::str_trim(response, " \n");

		if (response.empty() || response[0] != '{' || response[response.size() - 1] != '}')
			return;

		m_Map.clear();

		// 1er: recupere les lignes

		std::vector<std::string> tiles = Utils::str_split(response, ", ");
		std::vector<std::vector<std::string>> lines;
		std::vector<std::string> current_line;

		int32_t count = 0;
		for (std::string tileContent : tiles)
		{
			current_line.push_back(Utils::str_trim(tileContent, " \n\t{}"));
			count++;

			if (std::sqrt(count) == std::floor(std::sqrt(count))) {
				lines.push_back(current_line);
				current_line.clear();
			}
		}

		if (!current_line.empty())
			lines.push_back(current_line);

		// 2eme: les remplir pour quelles aient une taille egale

		size_t max = 0;
		for (std::vector<std::string> line : lines)
		{
			if (line.size() > max)
				max = line.size();
		}

		for (std::vector<std::string> &line : lines)
		{
			size_t diff = max - line.size();
			size_t eachSide = diff / 2;

			for (size_t i = 0; i < eachSide; i++)
			{
				line.insert(line.begin(), "");
				line.push_back("");
			}
		}

		m_Map = lines;
	}

	void ParseInventory(std::string response)
	{
		response = Utils::str_trim(response, " \n");

		if (response.empty() || response[0] != '{' || response[response.size() - 1] != '}')
			return;

		m_Inventory.clear();

		// remove first { and last }
		response = Utils::str_trim(response, " \t{}");

		std::vector<std::string> items = Utils::str_split(response, ", ");
		std::map<std::string, int32_t> inventory;

		for (std::string item : items)
		{
			std::vector<std::string> itemSplit = Utils::str_split(item, " ");
			if (itemSplit.size() != 2)
				continue;
			inventory.insert(std::pair<std::string, int32_t>(itemSplit[0], atoi(itemSplit[1].c_str())));
		}

		m_Inventory = inventory;
	}

	Pathfinding* FindPath(std::string target)
	{
		return new Pathfinding(m_Map, target);
	}

	Pathfinding* FindPath(std::vector<std::string> targets)
	{
		return new Pathfinding(m_Map, targets);
	}

	bool IsInventoryReponse(std::string response)
	{
		std::regex format2_regex("\\{nourriture \\d+, linemate \\d+, deraumere \\d+, sibur \\d+, mendiane \\d+, phiras \\d+, thystame \\d+\\}");
		return std::regex_match(response, format2_regex);
	}

	bool IsMapOrInventoryReponse(std::string response)
	{
		return std::regex_match(response, std::regex("\\{.*\\}"));
	}

	bool IsMapReponse(std::string response)
	{
		return IsMapOrInventoryReponse(response) && !IsInventoryReponse(response);
	}

	bool IsFoodInSight()
	{
		if (m_Map.size() == 0 || m_Map[0].size() == 0)
			return false;

		for (std::vector<std::string> line : m_Map)
		{
			for (std::string tile : line)
			{
				if (tile.find("nourriture") != std::string::npos)
					return true;
			}
		}
		return false;
	}

	bool IsOreInSight()
	{
		if (m_Map.size() == 0 || m_Map[0].size() == 0)
			return false;

		std::vector<std::string> ores = GetNeededOre();

		for (std::vector<std::string> line : m_Map)
		{
			for (std::string tile : line)
			{
				for (std::string ore: ores)
				{
					if (tile.find(ore) != std::string::npos)
						return true;
				}
			}
		}
		return false;
	}

	bool IsPlayerInSight()
	{
		if (m_Map.size() == 0 || m_Map[0].size() == 0)
			return false;

		for (std::vector<std::string> line : m_Map)
		{
			for (std::string tile : line)
			{
				if (tile.find("player") != std::string::npos)
					return true;
			}
		}
		return false;
	}

	bool IsWalkingOnFood()
	{
		if (m_Map.size() == 0 || m_Map[0].size() == 0)
			return false;
		return m_Map[0][m_Level].find("nourriture") != std::string::npos;
	}

	bool IsWalkingOnOre()
	{
		if (m_Map.size() == 0 || m_Map[0].size() == 0)
			return false;

		std::vector<std::string> ores = GetNeededOre();

		for (std::string ore: ores)
		{
			if (m_Map[0][m_Level].find(ore) != std::string::npos)
				return true;
		}
		return false;
	}

	bool HasEnoughFood()
	{
		if (m_Inventory.size() == 0 || m_Inventory.find("nourriture") == m_Inventory.end())
			return false;
		return m_Inventory["nourriture"] > 30 * 126;
	}

	bool HasPlayerOnCell()
	{
		if (m_Map.size() == 0 || m_Map[0].size() == 0)
			return false;
		return m_Map[0][m_Level].find("player") != std::string::npos;
	}

	bool HasEnoughOre()
	{
		auto requirements = Levels[m_Level - 1];
		for (auto const& [ore, amount] : requirements.ore)
		{
			if (m_Inventory.find(ore) == m_Inventory.end() || m_Inventory[ore] < amount)
				return false;
		}
		return true;
	}

	bool HasEnoughPlayer()
	{
		auto requirements = Levels[m_Level - 1];
		return requirements.nb_player <= m_NbPlayer;
	}

	std::vector<std::vector<std::string>>& GetMap()
	{
		return m_Map;
	}

	std::map<std::string, int32_t>& GetInventory()
	{
		return m_Inventory;
	}

	int GetLevel()
	{
		return m_Level;
	}

	int GetIncantationDirection()
	{
		return m_IncantationDirection;
	}

	void SetIncantationDirection(int direction)
	{
		m_IncantationDirection = direction;
	}

	bool CanJoinPlayer()
	{
		return m_IncantationDirection != -1;
	}

	std::vector<std::string> GetNeededOre()
	{
		std::map<std::string, int> neededOre = {{"linemate", 0}, {"deraumere", 0}, {"sibur", 0}, {"mendiane", 0}, {"phiras", 0}, {"thystame", 0}};
		for (int i = m_Level - 1; i < 7; i++)
		{
			auto requirements = Levels[i];
			for (auto const& [ore, amount] : requirements.ore)
			{
				neededOre[ore] += amount;
			}
		}
		for (auto const& [ore, amount] : m_Inventory)
		{
			neededOre[ore] -= amount;
		}
		std::vector<std::string> res;
		for (auto const& [ore, amount] : neededOre)
		{
			if (amount > 0)
				res.push_back(ore);
		}
		return res;
	}

	bool ArePlayersReady()
	{
		return m_NbPlayerReady == m_NbPlayer && !SlotAvailable();
	}

	void IncNbPlayerReady()
	{
		m_NbPlayerReady++;
	}

	bool SlotAvailable()
	{
		return m_NbPlayer < Levels[m_Level - 1].nb_player;
	}

	int GetNbPlayer()
	{
		return m_NbPlayer;
	}
};
