/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 08:40:27 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/13 11:12:24 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void)
{
	std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name)
{
	this->_name = name;
	this->_hitPoints = 10;
	this->_energyPoints = 10;
	this->_attackDamage = 0;

	std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap & copy)
{
	*this = copy;
	std::cout << "ClapTrap copy constructor called" << std::endl;
}

ClapTrap &	ClapTrap::operator=(const ClapTrap & copy)
{
	this->_name = copy.getName();
	this->_hitPoints = copy.getHitPoints();
	this->_energyPoints = copy.getEnergyPoints();
	this->_attackDamage = copy.getAttackDamage();

	std::cout << "ClapTrap assignation operator called" << std::endl;
	return (*this);
}

ClapTrap::~ClapTrap(void)
{
	std::cout << "ClapTrap destructor called" << std::endl;
}

void	ClapTrap::attack(const std::string & target)
{
	std::cout << "ClapTrap " << this->getName();
	std::cout << " attack " << target;
	std::cout << ", causing " << this->getHitPoints();
	std::cout << " points of damage!" << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	this->_attackDamage += amount;

	std::cout << "ClapTrap " << this->getName();
	std::cout << " take " << amount;
	std::cout << " points of damage!" << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (this->getEnergyPoints() < (int) amount)
	{
		std::cout << "ClapTrap " << this->getName();
		std::cout << " cannot be repaired (Energy left: 0)." << std::endl;
	}
	else
	{
		this->_attackDamage -= amount;
		this->_energyPoints -= amount;
		std::cout << "ClapTrap " << this->getName();
		std::cout << " has been repaired (Energy left: " << this->getEnergyPoints();
		std::cout << ")." << std::endl;
	}
}

void	ClapTrap::setName(std::string name)
{ this->_name = name; }

void	ClapTrap::setHitPoints(int hitpoints)
{ this->_hitPoints = hitpoints; }

void	ClapTrap::setEnergyPoints(int energypoints)
{ this->_energyPoints = energypoints; }

void	ClapTrap::setAttackDamage(int attackdamage)
{ this->_attackDamage = attackdamage; }

std::string	ClapTrap::getName(void) const
{ return (this->_name); }

int			ClapTrap::getHitPoints(void) const
{ return (this->_hitPoints); }

int			ClapTrap::getEnergyPoints(void) const
{ return (this->_energyPoints); }

int			ClapTrap::getAttackDamage(void) const
{ return (this->_attackDamage); }
