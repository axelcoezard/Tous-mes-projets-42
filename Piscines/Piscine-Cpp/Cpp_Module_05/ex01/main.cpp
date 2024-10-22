/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:34:22 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/21 12:16:05 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void)
{
	Bureaucrat *A = new Bureaucrat("Axel", 20);
	std::cout << A << std::endl;
	
	Bureaucrat *M = new Bureaucrat("Marie", 40);
	std::cout << M << std::endl;

	try {
		Form *formA = new Form("Adhesion-1", 30, 20);
		std::cout << formA << std::endl;

		A->signForm(formA);
		std::cout << formA << std::endl;
		delete formA;

		Form *formM = new Form("Adhesion-2", 30, 20);
		std::cout << formM << std::endl;

		M->signForm(formM);
		std::cout << formM << std::endl;
		delete formM;
	} catch (Form::GradeTooLowException &e) {
		std::cout << "Error: " << e.what() << std::endl;	
	}
	
	delete A;
	delete M;
	
	return (0);
}

