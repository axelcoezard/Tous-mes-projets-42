/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:32:40 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/14 12:39:17 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal(void)
{
	this->setType("Animal");
	std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(const Animal & copy)
{
	*this = copy;
	std::cout << "Animal copy constructor called" << std::endl;
}

Animal&	Animal::operator=(const Animal & copy)
{
	this->setType(copy.getType());
	std::cout << "Animal assignation operator called" << std::endl;
	return (*this);
}

Animal::~Animal(void)
{ std::cout << "Animal destructor called" << std::endl; }

void	Animal::makeSound(void) const
{ std::cout << "**Animal does a weird default sound**" << std::endl; }

std::string	Animal::getType(void) const
{ return (this->_type); }

void	Animal::setType(std::string type)
{ this->_type = type; }
