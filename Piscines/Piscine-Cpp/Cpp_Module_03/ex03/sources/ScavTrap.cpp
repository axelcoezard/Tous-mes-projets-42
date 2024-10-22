/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 09:55:58 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/13 14:58:54 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void)
{ std::cout << "ScavTrap default constructor called" << std::endl; }

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	this->_name = name;
	this->_hitPoints = 100;
	this->_energyPoints = 50;
	this->_attackDamage = 20;
	std::cout << "ScavTrap default constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap & copy)
{
	*this = copy;
	std::cout << "ScavTrap copy constructor called" << std::endl;
}

ScavTrap &	ScavTrap::operator=(const ScavTrap & copy)
{
	this->_name = copy.getName();
	this->_hitPoints = copy.getHitPoints();
	this->_energyPoints = copy.getEnergyPoints();
	this->_attackDamage = copy.getAttackDamage();

	std::cout << "ScavTrap assignation operator called" << std::endl;
	return (*this);
}

ScavTrap::~ScavTrap(void)
{
	std::cout << "ScavTrap destructor called" << std::endl;
}

void	ScavTrap::attack(const std::string & target)
{
	std::cout << "ScavTrap " << this->getName();
	std::cout << " attack " << target;
	std::cout << ", causing " << this->getHitPoints();
	std::cout << " points of damage!" << std::endl;
}

void	ScavTrap::takeDamage(unsigned int amount)
{
	this->_attackDamage = this->getAttackDamage() + amount;

	std::cout << "ScavTrap " << this->getName();
	std::cout << " take " << amount;
	std::cout << " points of damage!" << std::endl;
}

void	ScavTrap::beRepaired(unsigned int amount)
{
	if (this->getEnergyPoints() < (int) amount)
	{
		std::cout << "ScavTrap " << this->getName();
		std::cout << " cannot be repaired (Energy left: 0)." << std::endl;
	}
	else
	{
		this->_attackDamage = this->getAttackDamage() - amount;
		this->_energyPoints = this->getEnergyPoints() - amount;
		std::cout << "ScavTrap " << this->getName();
		std::cout << " has been repaired (Energy left: " << this->getEnergyPoints();
		std::cout << ")." << std::endl;
	}
}

void	ScavTrap::guardGate(void)
{
	std::cout << "ScavTrap " << this->getName();
	std::cout << " have enterred in Gate keeper mode." << std::endl;
}
