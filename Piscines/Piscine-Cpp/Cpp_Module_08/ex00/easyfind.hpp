/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 13:39:43 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/31 14:52:29 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdexcept>
#include <iostream>

class NotFoundException : public std::exception
{
	public:
		const char	*what(void) const throw() {
			return ("Not found exception");
		}	
};

template <typename T>
unsigned int	easyfind(T & container, int value)
{
	typename T::iterator i = container.begin();
	unsigned int	index = 0;

	while (i != container.end())
	{
		if (*i == value)
			return (index);
		i++, index++;
	}

	throw NotFoundException();
}
