/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:05:20 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/15 09:49:58 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource(void)
{
	for (int i = 0; i < 4; i++)
		this->setMateria(i, NULL);
}

MateriaSource::MateriaSource(const MateriaSource & copy)
{ *this = copy; }

MateriaSource&	MateriaSource::operator=(const MateriaSource & copy)
{
	for (int i = 0; i < 4; i++)
	{
		AMateria *m = copy.getMateria(i);
		if (m != NULL)
			this->_learned[i] = m->clone();
		else
			this->_learned[i] = NULL;
	}
	return (*this);
}

MateriaSource::~MateriaSource(void)
{ }

void	MateriaSource::learnMateria(AMateria* m)
{
	for (int i = 0; i < 4; i++)
	{
		if (this->getMateria(i) == NULL)
		{ this->setMateria(i, m->clone()); break; }
	}
}

AMateria*	MateriaSource::createMateria(std::string const & type)
{
	for (int i = 0; i < 4; i++)
	{
		AMateria *m = this->getMateria(i);
		if (m != NULL && m->getType() == type)
			return (m->clone());
	}
	return (NULL);
}

void	MateriaSource::setMateria(int i, AMateria	*m)
{
	if (i < 0 || i > 3)
		return ;
	this->_learned[i] = m;
}

AMateria	*MateriaSource::getMateria(int i) const
{
	if (i < 0 || i > 3)
		return (NULL);
	return (this->_learned[i]);
}
