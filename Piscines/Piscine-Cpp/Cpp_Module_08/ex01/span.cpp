/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 14:54:46 by acoezard          #+#    #+#             */
/*   Updated: 2022/01/03 21:40:53 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "span.hpp"

Span::Span(unsigned int N)
	: _N(N), _size(0)
{
	this->_items = new int[N];
}

Span::~Span(void)
{

}

void	Span::addNumber(int n)
{
	if (this->_size == this->_N)
		throw Span::NumberCannotBeAdded();
	this->_items[this->_size++] = n;
}


int		Span::shortestSpan(void)
{
	if (this->_size <= 1)
		throw Span::SpanCannotBeFound();

	unsigned int	res = 4294967295;
	unsigned int	diff = 0;
	for (unsigned int i = 0; i < this->_N - 1; i++)
	{
		diff = abs(this->_items[i] - this->_items[i + 1]);
		if (diff < res) res = diff;
	}
	return (res);
}

int		Span::longestSpan(void)
{
	if (this->_size <= 1)
		throw Span::SpanCannotBeFound();

	unsigned int	res = 0;
	unsigned int	diff = 0;
	for (unsigned int i = 0; i < this->_N - 1; i++)
	{
		diff = abs(this->_items[i] - this->_items[i + 1]);
		if (diff > res) res = diff;
	}
	return (res);
}
