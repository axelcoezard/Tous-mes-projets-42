/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:49:02 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/12 21:57:14 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point(void) : _x(0), _y(0)
{ }

Point::Point(const Point & copy) : _x(copy._x), _y(copy._y)
{ }

Point::Point(const Fixed & x, const Fixed & y) : _x(x), _y(y)
{ }

Point::~Point(void)
{ }

Point&	Point::operator=(const Point & copy)
{
	(Fixed&) this->_x = copy._x;
	(Fixed&) this->_y = copy._y;
	std::cout << copy._x << " " << this->_x << std::endl;
	std::cout << copy._y << " " << this->_y << std::endl;
	return (*this);
}

Fixed	Point::getX(void) const
{ return (Fixed) (this->_x); }

Fixed	Point::getY(void) const
{ return (Fixed) (this->_y); }
