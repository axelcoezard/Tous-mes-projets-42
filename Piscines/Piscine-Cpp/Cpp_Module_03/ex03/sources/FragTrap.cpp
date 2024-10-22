/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 09:55:58 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/13 14:59:41 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap(void)
{ std::cout << "FragTrap default constructor called" << std::endl; }

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	this->_name = name;
	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;

	std::cout << "FragTrap default constructor called" << std::endl;
}

FragTrap::FragTrap(const FragTrap & copy)
{
	*this = copy;
	std::cout << "FragTrap copy constructor called" << std::endl;
}

FragTrap &	FragTrap::operator=(const FragTrap & copy)
{
	this->_name = copy.getName();
	this->_hitPoints = copy.getHitPoints();
	this->_energyPoints = copy.getEnergyPoints();
	this->_attackDamage = copy.getAttackDamage();

	std::cout << "FragTrap assignation operator called" << std::endl;
	return (*this);
}

FragTrap::~FragTrap(void)
{
	std::cout << "FragTrap destructor called" << std::endl;
}

void	FragTrap::attack(const std::string & target)
{
	std::cout << "FragTrap " << this->getName();
	std::cout << " attack " << target;
	std::cout << ", causing " << this->getHitPoints();
	std::cout << " points of damage!" << std::endl;
}

void	FragTrap::takeDamage(unsigned int amount)
{
	this->_attackDamage = this->getAttackDamage() + amount;

	std::cout << "FragTrap " << this->getName();
	std::cout << " take " << amount;
	std::cout << " points of damage!" << std::endl;
}

void	FragTrap::beRepaired(unsigned int amount)
{
	if (this->getEnergyPoints() < (int) amount)
	{
		std::cout << "FragTrap " << this->getName();
		std::cout << " cannot be repaired (Energy left: 0)." << std::endl;
	}
	else
	{
		this->_attackDamage = this->getAttackDamage() - amount;
		this->_energyPoints = this->getEnergyPoints() - amount;
		std::cout << "FragTrap " << this->getName();
		std::cout << " has been repaired (Energy left: " << this->getEnergyPoints();
		std::cout << ")." << std::endl;
	}
}

void	FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << this->getName();
	std::cout << " says \"Let's do a high fives together!\"" << std::endl;
}
