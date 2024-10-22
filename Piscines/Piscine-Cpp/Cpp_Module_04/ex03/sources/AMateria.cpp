/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:39:43 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/14 15:51:23 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria(void)
{ }

AMateria::AMateria(const std::string & type)
{
	this->setType(type);
}

AMateria::AMateria(const AMateria & copy)
{ *this = copy; }

AMateria&	AMateria::operator=(const AMateria & copy)
{
	this->setType(copy.getType());
	return (*this);
}

AMateria::~AMateria(void)
{ }

void	AMateria::use(ICharacter & target)
{
	(void) target;
}

void	AMateria::setType(std::string type)
{ this->_type = type; }

const std::string&	AMateria::getType(void) const
{ return (this->_type); }
