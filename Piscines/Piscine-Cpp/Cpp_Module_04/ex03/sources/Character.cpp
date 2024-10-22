/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:20:01 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/14 15:58:13 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

Character::Character(void)
{
	for (int i = 0; i < 4; i++)
		this->setMateria(i, NULL);
}

Character::Character(std::string name)
{
	this->setName(name);
	for (int i = 0; i < 4; i++)
		this->setMateria(i, NULL);
}

Character::Character(const Character & copy)
{ *this = copy; }

Character&	Character::operator=(const Character & copy)
{
	this->setName(copy.getName());
	for (int i = 0; i < 4; i++)
	{
		AMateria *m = copy.getMateria(i);
		if (m == NULL)
			continue;
		this->equip(m->clone());
	}
	return (*this);
}

Character::~Character(void)
{
	for (int i = 0; i < 4; i++)
	{
		AMateria *m = this->getMateria(i);
		if (m == NULL)
			continue;
		delete m;
	}
}

void	Character::setName(std::string name)
{ this->_name = name; }

const std::string&	Character::getName(void) const
{ return (this->_name); }

void	Character::setMateria(int i, AMateria *m)
{
	if (i >= 0 && i <= 3)
		this->_inventory[i] = m;
}
AMateria*	Character::getMateria(int i) const
{
	if (i < 0 || i > 3)
		return (NULL);
	return (this->_inventory[i]);
}

void	Character::equip(AMateria *m)
{
	for (int i = 0; i < 4; i++)
	{
		if (this->getMateria(i) == NULL)
		{ this->setMateria(i, m); break; }
	}
}

void	Character::unequip(int i)
{
	if (this->getMateria(i) != NULL)
		this->setMateria(i, NULL);
}

void	Character::use(int i, ICharacter& target)
{
	if (i < 0 || i > 3)
		return ;
	AMateria *m = this->getMateria(i);
	if (m == NULL)
		return ;
	m->use(target);
}
