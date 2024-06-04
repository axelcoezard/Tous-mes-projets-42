/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Console.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:11:00 by acoezard          #+#    #+#             */
/*   Updated: 2024/02/12 10:17:45 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Console.hpp"
#include "Utils.hpp"

void Console::Print(std::string type, std::string str, std::string color)
{
	std::cout << Console::RESET << "[" << color << type << Console::RESET << "] " << Utils::str_trim(str, "\n") << std::endl;
}

void Console::Log(std::string str)
{
	Console::Print("LOG", str, Console::GREEN);
}

void Console::Error(std::string str)
{
	Console::Print("ERROR", str, Console::RED);
}
