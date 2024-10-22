/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:53:38 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/15 10:23:38 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(void) : Animal()
{
	this->setType("Dog");
	std::cout << "Dog default constructor called" << std::endl;
}

Dog::Dog(const Dog & copy)
{
	*this = copy;
	std::cout << "Dog copy constructor called" << std::endl;
}

Dog &	Dog::operator=(const Dog & copy)
{
	this->setType(copy.getType());
	std::cout << "Dog assignation operator called" << std::endl;
	return (*this);
}

void	Dog::makeSound(void) const
{ std::cout << "**Dog does a " << this->getType() << " sound**" << std::endl; }

Dog::~Dog(void)
{ std::cout << "Dog destructor called" << std::endl; }

