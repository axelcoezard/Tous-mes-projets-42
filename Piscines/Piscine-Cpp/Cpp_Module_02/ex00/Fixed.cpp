/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:26:17 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/10 14:39:11 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(void)
{
	std::cout << "Default constructor called" << std::endl;
	this->setRawBits(0);
}

Fixed::Fixed(const Fixed & copy)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = copy;
}

void	Fixed::operator=(const Fixed & copy)
{
	std::cout << "Assignation operator called" << std::endl;
	this->setRawBits(copy.getRawBits());
}

int		Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (this->_value);
}

void	Fixed::setRawBits(const int raw)
{ this->_value = raw; }

Fixed::~Fixed(void)
{ std::cout << "Destructor called" << std::endl; }
