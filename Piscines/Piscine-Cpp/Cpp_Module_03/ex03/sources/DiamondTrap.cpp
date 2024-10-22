/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 13:29:52 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/13 15:10:20 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap(void)
{ std::cout << "DiamondTrap default constructor called" << std::endl; }

DiamondTrap::DiamondTrap(std::string name) :
	FragTrap(name + "_clap_name"), ScavTrap(name + "_clap_name")
{
	this->_name = name;
	this->_hitPoints = FragTrap::getHitPoints();
	this->_energyPoints = ScavTrap::getEnergyPoints();
	this->_attackDamage = FragTrap::getAttackDamage();

	std::cout << "DiamondTrap default constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap & copy)
{
	*this = copy;
	std::cout << "DiamondTrap copy constructor called" << std::endl;
}

DiamondTrap &	DiamondTrap::operator=(const DiamondTrap & copy)
{
	this->_name = copy.getName();
	this->_hitPoints = copy.getHitPoints();
	this->_energyPoints = copy.getEnergyPoints();
	this->_attackDamage = copy.getAttackDamage();

	std::cout << "DiamondTrap assignation operator called" << std::endl;
	return (*this);
}

DiamondTrap::~DiamondTrap(void)
{ std::cout << "DiamondTrap destructor called" << std::endl; }

void	DiamondTrap::attack(const std::string & target)
{ ScavTrap::attack(target); }

void	DiamondTrap::takeDamage(unsigned int amount)
{
	this->_attackDamage = this->getAttackDamage() + amount;

	std::cout << "DiamondTrap " << this->getName();
	std::cout << " take " << amount;
	std::cout << " points of damage!" << std::endl;
}

void	DiamondTrap::beRepaired(unsigned int amount)
{
	if (this->getEnergyPoints() < (int) amount)
	{
		std::cout << "DiamondTrap " << this->getName();
		std::cout << " cannot be repaired (Energy left: 0)." << std::endl;
	}
	else
	{
		this->_attackDamage = this->getAttackDamage() - amount;
		this->_energyPoints = this->getEnergyPoints() - amount;
		std::cout << "DiamondTrap " << this->getName();
		std::cout << " has been repaired (Energy left: " << this->getEnergyPoints();
		std::cout << ")." << std::endl;
	}
}

void	DiamondTrap::whoAmI(void)
{
	std::cout << "DiamondTrap name is " << this->getName();
	std::cout << " and ClapTrap one is " << ClapTrap::getName() << std::endl;
}

std::string	DiamondTrap::getName(void) const
{ return (this->_name); }
