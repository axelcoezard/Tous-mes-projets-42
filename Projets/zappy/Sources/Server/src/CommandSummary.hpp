#pragma once

#include "Game/Client.hpp"

struct CommandSummary
{
	std::string name;
	std::vector<std::string> arguments;

	Client* player;

	int32_t remainingDelay;
};
