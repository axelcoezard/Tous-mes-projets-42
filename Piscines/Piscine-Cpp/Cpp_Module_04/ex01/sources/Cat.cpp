/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:53:02 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/14 13:26:48 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Brain.hpp"

Cat::Cat(void) : Animal()
{
	this->setType("Cat");
	this->setBrain(new Brain());
	std::cout << "Cat default constructor called" << std::endl;
}

Cat::Cat(const Cat & copy)
{
	*this = copy;
	std::cout << "Cat copy constructor called" << std::endl;
}

Cat&	Cat::operator=(const Cat & copy)
{
	this->setType(copy.getType());
	this->setBrain(new Brain(*copy.getBrain()));
	std::cout << "Cat assignation operator called" << std::endl;
	return (*this);
}

void	Cat::makeSound(void) const
{ std::cout << "**Cat does a cat sound**" << std::endl; }

Cat::~Cat(void)
{
	delete this->getBrain();
	std::cout << "Cat destructor called" << std::endl;
}

Brain	*Cat::getBrain(void) const
{ return (this->_brain); }

void	Cat::setBrain(Brain	*brain)
{ this->_brain = brain; }
