/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:34:22 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/15 15:30:53 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"

int main(void)
{
	try
	{
		Bureaucrat *A = new Bureaucrat("A", 0);
		std::cout << A << std::endl;
		delete A;
	}
	catch (Bureaucrat::GradeTooHighException& e)
	{ std::cout << e.what() << std::endl; }
	catch (Bureaucrat::GradeTooLowException& e)
	{ std::cout << e.what() << std::endl; }
	
	try
	{
		Bureaucrat *B = new Bureaucrat("B", 151);
		std::cout << B << std::endl;
		delete B;
	}
	catch (Bureaucrat::GradeTooHighException& e)
	{ std::cout << e.what() << std::endl; }
	catch (Bureaucrat::GradeTooLowException& e)
	{ std::cout << e.what() << std::endl; }
	
	
	try
	{
		Bureaucrat *C = new Bureaucrat("C", 20);
		std::cout << C << std::endl;
		delete C;
	}
	catch (Bureaucrat::GradeTooHighException& e)
	{ std::cout << e.what() << std::endl; }
	catch (Bureaucrat::GradeTooLowException& e)
	{ std::cout << e.what() << std::endl; }
	return (0);
}

