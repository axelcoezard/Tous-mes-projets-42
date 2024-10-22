/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:26:17 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/12 22:05:06 by acoezard         ###   ########.fr       */
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
	this->_value = (int) roundf(n * (1 << this->_bits));
}

Fixed::~Fixed(void)
{ std::cout << "Destructor called" << std::endl; }

Fixed&	Fixed::operator=(const Fixed & copy)
{
	std::cout << "Assignation operator called" << std::endl;
	this->setRawBits(copy.getRawBits());
	return (*this);
}

Fixed	Fixed::operator+(const Fixed & n) const
{ return (Fixed(this->toFloat() + n.toFloat())); }

Fixed	Fixed::operator-(const Fixed & n) const
{ return (Fixed(this->toFloat() - n.toFloat())); }

Fixed	Fixed::operator*(const Fixed & n) const
{ return (Fixed((float) this->toFloat() * (float) n.toFloat())); }

Fixed	Fixed::operator/(const Fixed & n) const
{ return (Fixed((float) this->toFloat() / (float) n.toFloat())); }

bool	Fixed::operator>(const Fixed & n) const
{ return (this->_value > n.getRawBits()); }

bool	Fixed::operator<(const Fixed & n) const
{ return (this->_value < n.getRawBits()); }

bool	Fixed::operator>=(const Fixed & n) const
{ return (this->_value >= n.getRawBits()); }

bool	Fixed::operator<=(const Fixed & n) const
{ return (this->_value <= n.getRawBits()); }

bool	Fixed::operator==(const Fixed & n) const
{ return (this->_value == n.getRawBits()); }

bool	Fixed::operator!=(const Fixed & n) const
{ return !(*this == n); }

Fixed&	Fixed::operator++(void)
{
	this->_value++;
	return (*this);
}

Fixed	Fixed::operator++(int)
{
	Fixed	newFixed(*this);
	++(*this);
	return (newFixed);
}

Fixed&	Fixed::operator--(void)
{
	this->_value--;
	return (*this);
}

Fixed	Fixed::operator--(int)
{
	Fixed	newFixed(*this);
	--(*this);
	return (newFixed);
}

int		Fixed::getRawBits(void) const
{ return (this->_value); }

void	Fixed::setRawBits(const int raw)
{ this->_value = raw; }

int		Fixed::toInt(void) const
{ return (int) (this->_value >> this->_bits); }

float	Fixed::toFloat(void) const
{ return ((float) this->_value / (1 << this->_bits)); }

const Fixed&	Fixed::min(const Fixed & a, const Fixed & b)
{ return (a > b ? b : a); }

const Fixed&	Fixed::max(const Fixed & a, const Fixed & b)
{ return (a > b ? a : b); }

std::ostream	&operator<<(std::ostream & stream, const Fixed & x)
{
	stream << x.toFloat();
	return (stream);
}
