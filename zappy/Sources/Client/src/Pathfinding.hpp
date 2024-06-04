#pragma once

#define COST 7
#include "ResourceType.hpp"

class Pathfinding
{
private:
	int cost = 0;
	std::vector<std::string> movement;

	int pos_x;
	int pos_y;

	void FindPath(int target_x, int target_y)
	{
		int gauche = 0;
		while (pos_y != target_y)
		{
			movement.push_back("avance");
			pos_y++;
			cost += COST;
		}
		if (pos_x > target_x)
		{
			movement.push_back("gauche");
			gauche = 1;
			cost += COST;
		}
		else if (pos_x < target_x)
		{
			movement.push_back("droite");
			cost += COST;
		}
		while (pos_x != target_x)
		{
			movement.push_back("avance");
			gauche ? pos_x-- : pos_x++;
			cost += COST;
		}
	}

	std::tuple<int, int> FindTarget(std::vector<std::vector<std::string>> map, std::string target)
	{
		int target_x = 0;
		int target_y = std::floor((float) map[0].size() / 2.0f);
		float min_distance = -1;
		for (size_t i = 0; i < map.size(); i++)
		{
			for (size_t j = 0; j < map[i].size(); j++)
			{
				if (map[i][j].find(target) != std::string::npos)
				{
					float distance = CalculateDistance(pos_x, pos_y, j, i);
					if (min_distance == -1 || distance < min_distance)
					{
						min_distance = distance;
						target_x = j;
						target_y = i;
					}
				}
			}
		}
		return {target_x, target_y};
	}

public:
	Pathfinding(std::vector<std::vector<std::string>> map, std::string target)
	{
		pos_x = std::floor((float) map.size() / 2.0f);
		pos_y = 0;

		auto [target_x, target_y] = FindTarget(map, target);
		FindPath(target_x, target_y);
	}

	Pathfinding(std::vector<std::vector<std::string>> map, std::vector<std::string> target)
	{
		pos_x = std::floor((float) map.size() / 2.0f);
		pos_y = 0;

		float min_distance = static_cast<float>(INT32_MAX);
		int32_t min_x = 0;
		int32_t min_y = 0;

		for (auto &t : target)
		{
			auto [target_x, target_y] = FindTarget(map, t);

			float distance = CalculateDistance(pos_x, pos_y, target_x, target_y);
			if (distance < min_distance)
			{
				min_distance = distance;
				min_x = target_x;
				min_y = target_y;
			}
		}
		std::cout << "min_x: " << min_x << " min_y: " << min_y << std::endl;

		FindPath(min_x, min_y);
	}

	~Pathfinding() {}

	int GetCost() const
	{
		return cost;
	}

	int GetNbMoves()
	{
		return movement.size();
	}

	float CalculateDistance(int x, int y, int target_x, int target_y)
	{
		return (abs(x - target_x) + abs(y - target_y));
	}

	std::vector<std::string> GetMovement() const
	{
		return movement;
	}
};
