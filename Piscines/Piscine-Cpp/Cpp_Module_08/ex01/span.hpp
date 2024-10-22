/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 14:54:04 by acoezard          #+#    #+#             */
/*   Updated: 2022/01/03 21:40:44 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <exception>
#include <cmath>

class Span
{
	private:
		unsigned int	_N;
		unsigned int	_size;
		int				*_items;
	public:
		Span(unsigned int N);
		~Span(void);

		void	addNumber(int n);
		int		shortestSpan(void);
		int		longestSpan(void);

		class	NumberCannotBeAdded : public std::exception
		{
			public:
				const char *what() const throw()
				{ return ("Number cannot be added."); }
		};

		class	SpanCannotBeFound : public std::exception
		{
			public:
				const char *what() const throw()
				{ return("Span cannot be found."); }
		};
};
