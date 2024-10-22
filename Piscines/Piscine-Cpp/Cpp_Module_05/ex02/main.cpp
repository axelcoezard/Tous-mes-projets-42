/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:34:22 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/29 16:54:54 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main(void)
{
	Bureaucrat *A = new Bureaucrat("Axel", 1);
	std::cout << A << std::endl;
	
	try {
		Form *formS = new ShrubberyCreationForm("maison");
		Form *formR = new RobotomyRequestForm("Mathias");
		Form *formP = new PresidentialPardonForm("Mathias");
		std::cout << formS << std::endl;
		std::cout << formR << std::endl;
		std::cout << formP << std::endl;

		A->signForm(formS);
		A->executeForm(*formS);

		A->signForm(formR);
		A->executeForm(*formR);

		A->signForm(formP);
		A->executeForm(*formP);

		std::cout << formS << std::endl;
		std::cout << formR << std::endl;
		std::cout << formP << std::endl;
		delete formS;
	} catch (Form::GradeTooLowException &e) {
		std::cout << "Error: " << e.what() << std::endl;	
	} catch (Form::NotSignedException &e) {
		std::cout << "Error: " << e.what() << std::endl;	
	} catch (Form::GradeTooHighException &e) {
		std::cout << "Error: " << e.what() << std::endl;	
	}
	
	delete A;
	
	return (0);
}

