/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 12:52:51 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/30 13:02:37 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

template<typename T>
void	swap(T & a, T & b)
{
	T	c = a; 
	a = b;
	b = c;
}

template<typename T>
T	min(T a, T b)
{
	if (a < b)
		return (a);
	return (b);
}

template<typename T>
T	max(T a, T b)
{
	if (a > b)
		return (a);
	return (b);
}
