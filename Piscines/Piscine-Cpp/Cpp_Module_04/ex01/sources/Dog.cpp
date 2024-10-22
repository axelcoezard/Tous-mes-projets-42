/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:53:38 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/14 13:26:57 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Brain.hpp"

Dog::Dog(void) : Animal()
{
	this->setType("Dog");
	this->setBrain(new Brain());
	std::cout << "Dog default constructor called" << std::endl;
}

Dog::Dog(const Dog & copy)
{
	*this = copy;
	std::cout << "Dog copy constructor called" << std::endl;
}

Dog&	Dog::operator=(const Dog & copy)
{
	this->setType(copy.getType());
	this->setBrain(new Brain(*copy.getBrain()));
	std::cout << "Dog assignation operator called" << std::endl;
	return (*this);
}

void	Dog::makeSound(void) const
{ std::cout << "**Dog does a dog sound**" << std::endl; }

Dog::~Dog(void)
{
	delete this->getBrain();
	std::cout << "Dog destructor called" << std::endl;
}

Brain	*Dog::getBrain(void) const
{ return (this->_brain); }

void	Dog::setBrain(Brain	*brain)
{ this->_brain = brain; }
