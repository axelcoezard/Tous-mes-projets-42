/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:53:02 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/15 10:22:52 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(void) : Animal()
{
	this->setType("Cat");
	std::cout << "Cat default constructor called" << std::endl;
}

Cat::Cat(const Cat & copy)
{
	*this = copy;
	std::cout << "Cat copy constructor called" << std::endl;
}

Cat &	Cat::operator=(const Cat & copy)
{
	this->setType(copy.getType());
	std::cout << "Cat assignation operator called" << std::endl;
	return (*this);
}

void	Cat::makeSound(void) const
{ std::cout << "**Cat does a " << this->getType() << " sound**" << std::endl; }

Cat::~Cat(void)
{ std::cout << "Cat destructor called" << std::endl; }
