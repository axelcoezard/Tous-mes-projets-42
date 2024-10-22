/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:23:12 by acoezard          #+#    #+#             */
/*   Updated: 2022/01/03 14:13:03 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base *	generate(void)
{
	srand(time(NULL));
	switch (rand() % 3)
	{
		case 1:
			return (new A());
		case 2:
			return (new B());
		default:
			return (new C());
	}
}

void	identify(Base * p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
}

void	identify(Base & p)
{
	try {
		(void) dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
	}
	catch (std::exception & e) {
		try {
			(void) dynamic_cast<B&>(p);
			std::cout << "B" << std::endl;
		}
		catch (std::exception & e) {
			try {
				(void) dynamic_cast<C&>(p);
				std::cout << "C" << std::endl;
			}
			catch (std::exception & e) { }
		}
	}
}

int main(void)
{
	Base *base;
	
	base = generate();
    identify(base);
    identify(*base);
	return (0);
}

