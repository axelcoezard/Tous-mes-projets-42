/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:46:22 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/12 21:56:11 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cmath>
#include "Fixed.hpp"

class Point
{
	private:
		const Fixed _x;
		const Fixed _y;
	public:
		Point(void);
		Point(const Point & copy);
		Point(const Fixed & x, const Fixed & y);
		~Point(void);

		Point&	operator=(const Point & copy);

		Fixed	getX(void) const;
		Fixed	getY(void) const;
};

bool	bsp(const Point A, const Point B, const Point C, const Point x);
