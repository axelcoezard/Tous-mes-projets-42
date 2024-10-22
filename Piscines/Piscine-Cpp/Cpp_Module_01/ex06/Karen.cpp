/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Karen.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:17:20 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/09 17:58:18 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Karen.hpp"

void	Karen::debug(void)
{
	std::cout << "I love to get extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I just love it!";
	std::cout << std::endl;
}

void	Karen::info(void)
{
	std::cout << "I cannot believe adding extra bacon cost more money. You don’t put enough! If you did I would not have to ask for it!";
	std::cout << std::endl;
}

void	Karen::warning(void)
{
	std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming here for years and you just started working here last month.";
	std::cout << std::endl;
}

void	Karen::error(void)
{
	std::cout << "This is unacceptable, I want to speak to the manager now.";
	std::cout << std::endl;
}

Karen::Karen(void)
{
	this->_keys[0] = "DEBUG";
	this->_fcts[0] = &Karen::debug;
	this->_keys[1] = "INFO";
	this->_fcts[1] = &Karen::info;
	this->_keys[2] = "WARNING";
	this->_fcts[2] = &Karen::warning;
	this->_keys[3] = "ERROR";
	this->_fcts[3] = &Karen::error;
}

void	Karen::complain(std::string level)
{
	for (int i = 0; i < 4; i++)
	{
		if (this->_keys[i] == level)
		{
			(void)(this->*_fcts[i])();
			break ;
		}
	}
}

Karen::~Karen(void)
{ }
