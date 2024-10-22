/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:34:22 by acoezard          #+#    #+#             */
/*   Updated: 2022/01/03 09:37:42 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Intern.hpp"

int main(void)
{
	Intern A;
	
	try {
		Form*	form = A.makeForm("robotomy request", "Bender");
		delete form;
	} catch (Intern::FormDoesNotExistException &e) {
		std::cout << "Error: " << e.what() << std::endl;	
	}

	try {
		Form*	form = A.makeForm("robotomy test", "Bender");
		delete form;
	} catch (Intern::FormDoesNotExistException &e) {
		std::cout << "Error: " << e.what() << std::endl;	
	}	
	return (0);
}

