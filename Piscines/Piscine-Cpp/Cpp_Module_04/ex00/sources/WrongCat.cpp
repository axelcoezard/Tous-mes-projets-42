/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:53:02 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/15 11:32:26 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat(void)
{
	this->setType("WrongCat");
	std::cout << "WrongCat default constructor called" << std::endl;
}

WrongCat::WrongCat(const WrongCat & copy)
{
	*this = copy;
	std::cout << "WrongCat copy constructor called" << std::endl;
}

WrongCat &	WrongCat::operator=(const WrongCat & copy)
{
	this->setType(copy.getType());
	std::cout << "WrongCat assignation operator called" << std::endl;
	return (*this);
}

WrongCat::~WrongCat(void)
{ std::cout << "WrongCat destructor called" << std::endl; }

void	WrongCat::makeSound(void) const
{ std::cout << "**WrongCat does " << this->_type << " sound**" << std::endl; }
