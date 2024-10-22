/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:50:14 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/14 15:36:16 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice(void) : AMateria("ice")
{ }

Ice::Ice(const Ice & copy)
{ *this = copy; }

Ice&	Ice::operator=(const Ice & copy)
{
	this->setType(copy.getType());
	return (*this);
}

Ice::~Ice(void)
{ }

Ice*	Ice::clone(void) const
{
	return (new Ice(*this));
}

void	Ice::use(ICharacter& target)
{ std::cout << "* shoots an ice bolt at " << target.getName() << " *\n"; }
