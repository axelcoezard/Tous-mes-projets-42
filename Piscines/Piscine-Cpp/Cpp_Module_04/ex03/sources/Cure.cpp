/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nCure.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:26:41 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/14 15:26:50 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure(void) : AMateria("cure")
{ ; }

Cure::Cure(const Cure & copy)
{
	*this = copy;
}

Cure&	Cure::operator=(const Cure & copy)
{
	this->setType(copy.getType());
	return (*this);
}

Cure::~Cure(void)
{ }

Cure*	Cure::clone(void) const
{ return (new Cure(*this)); }

void	Cure::use(ICharacter& target)
{ std::cout << "* heals " << target.getName() << "'s wounds *\n"; }
