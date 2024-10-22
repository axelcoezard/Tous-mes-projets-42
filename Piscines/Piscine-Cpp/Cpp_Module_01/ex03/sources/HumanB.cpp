/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:11:54 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/09 12:25:00 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name)
{ this->_name = name; }

void	HumanB::attack(void)
{
	std::cout << this->_name;
	std::cout << " attacks with his ";
	std::cout << this->_weapon->getType();
	std::cout << std::endl;
}

void	HumanB::setWeapon(Weapon & weapon)
{ this->_weapon = &weapon; }

HumanB::~HumanB(void)
{ }
