/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 14:53:49 by acoezard          #+#    #+#             */
/*   Updated: 2022/01/03 21:39:56 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "span.hpp"

int main(void)
{
	try {
		Span sp = Span(5);
		sp.addNumber(5);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}
	catch (const std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	
	try {
		Span sp = Span(5);
		sp.addNumber(1);
		sp.addNumber(2);
		sp.addNumber(3);
		sp.addNumber(4);
		sp.addNumber(5);
		sp.addNumber(6);
	}
	catch (const std::exception & e) {
		std::cerr << e.what() << std::endl;
	}

	try {
		Span sp = Span(3);
		sp.addNumber(5);
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}
	catch (const std::exception & e) {
		std::cerr << e.what() << std::endl;
	}

	try {
		Span sp = Span(3);
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}
	catch (const std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}

