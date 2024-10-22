/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:21:45 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/10 14:40:25 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cmath>

class Fixed
{
	private:
		static const int _bits = 8;
		int	_value;
	public:
		Fixed(void);
		Fixed(const Fixed & copy);
		Fixed(const int n);
		Fixed(const float n);
		~Fixed(void);

		Fixed&	operator=(const Fixed & copy);
		Fixed	operator+(const Fixed & n) const;
		Fixed	operator-(const Fixed & n) const;
		Fixed	operator*(const Fixed & n) const;
		Fixed	operator/(const Fixed & n) const;

		bool	operator>(const Fixed & n) const;
		bool	operator<(const Fixed & n) const;
		bool	operator>=(const Fixed & n) const;
		bool	operator<=(const Fixed & n) const;
		bool	operator==(const Fixed & n) const;
		bool	operator!=(const Fixed & n) const;

		Fixed&	operator++(void);
		Fixed	operator++(int);
		Fixed&	operator--(void);
		Fixed	operator--(int);

		int		getRawBits(void) const;
		void	setRawBits(const int raw);
		int		toInt(void) const;
		float	toFloat(void) const;

		const static Fixed&	min(const Fixed & a, const Fixed & b);
		const static Fixed&	max(const Fixed & a, const Fixed & b);
};

std::ostream	&operator<<(std::ostream & stream, const Fixed & fixe);
