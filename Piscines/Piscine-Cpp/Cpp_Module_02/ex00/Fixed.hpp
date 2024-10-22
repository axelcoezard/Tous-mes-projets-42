/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:21:45 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/10 14:38:29 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class Fixed
{
	private:
		static const int _bits = 8;
		int	_value;
	public:
		Fixed(void);
		Fixed(const Fixed & copy);
		~Fixed(void);

		void	operator=(const Fixed & copy);
		int		getRawBits(void) const;
		void	setRawBits(const int raw);
};
