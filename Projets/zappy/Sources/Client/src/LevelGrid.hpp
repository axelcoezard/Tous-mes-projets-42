#pragma once

#include "../../Common/src/ResourceType.hpp"

struct Level_Requirement
{
    int nb_player;
    std::map<std::string, int> ore;
};

    std::array<Level_Requirement, 7> Levels = {
        {
            {1, {{"linemate", 1}, {"deraumere", 0}, {"sibur", 0}, {"mendiane", 0}, {"phiras", 0}, {"thystame", 0}}},
            {2, {{"linemate", 1}, {"deraumere", 1}, {"sibur", 1}, {"mendiane", 0}, {"phiras", 0}, {"thystame", 0}}},
            {2, {{"linemate", 2}, {"deraumere", 0}, {"sibur", 1}, {"mendiane", 0}, {"phiras", 2}, {"thystame", 0}}},
            {4, {{"linemate", 1}, {"deraumere", 1}, {"sibur", 2}, {"mendiane", 0}, {"phiras", 1}, {"thystame", 0}}},
            {4, {{"linemate", 1}, {"deraumere", 2}, {"sibur", 1}, {"mendiane", 3}, {"phiras", 0}, {"thystame", 0}}},
            {6, {{"linemate", 1}, {"deraumere", 2}, {"sibur", 3}, {"mendiane", 0}, {"phiras", 1}, {"thystame", 0}}},
            {6, {{"linemate", 2}, {"deraumere", 2}, {"sibur", 2}, {"mendiane", 2}, {"phiras", 2}, {"thystame", 1}}},
        }
    };