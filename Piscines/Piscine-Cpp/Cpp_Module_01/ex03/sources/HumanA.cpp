/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:28:39 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/09 12:25:26 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon & weapon)
{
	this->_name = name;
	this->_weapon = &weapon;
}

void	HumanA::attack(void)
{
	std::cout << this->_name;
	std::cout << " attacks with his ";
	std::cout << this->_weapon->getType();
	std::cout << std::endl;
}

HumanA::~HumanA(void)
{ }
