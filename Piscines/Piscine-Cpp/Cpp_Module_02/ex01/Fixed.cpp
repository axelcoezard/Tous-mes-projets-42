/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:26:17 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/12 22:04:13 by acoezard         ###   ########.fr       */
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

Fixed::Fixed(const int n)
{
	std::cout << "Int constructor called" << std::endl;
	this->_value = n << this->_bits;
}

Fixed::Fixed(const float n)
{
	std::cout << "Float constructor called" << std::endl;
	this->_value = roundf(n * (1 << this->_bits));
}

Fixed&	Fixed::operator=(const Fixed & copy)
{
	std::cout << "Assignation operator called" << std::endl;
	this->setRawBits(copy.getRawBits());
	return (*this);
}

int		Fixed::getRawBits(void) const
{ return (this->_value); }

void	Fixed::setRawBits(const int raw)
{ this->_value = raw; }

int		Fixed::toInt(void) const
{ return (int) (this->_value >> this->_bits); }

float	Fixed::toFloat(void) const
{ return ((float) this->_value / (1 << this->_bits)); }

Fixed::~Fixed(void)
{ std::cout << "Destructor called" << std::endl; }

std::ostream	&operator<<(std::ostream & stream, const Fixed & x)
{
	stream << x.toFloat();
	return (stream);
}
