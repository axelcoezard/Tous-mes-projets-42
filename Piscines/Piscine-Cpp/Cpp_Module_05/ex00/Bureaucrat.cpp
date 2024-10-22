/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 12:55:51 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/29 16:57:23 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(void)
	: _name("default"), _grade(150)
{ }

Bureaucrat::Bureaucrat(std::string name, int grade)
	: _name(name), _grade(grade)
{
	if (this->_grade > 150)
		throw Bureaucrat::GradeTooLowException(); 
	if (this->_grade < 1)
		throw Bureaucrat::GradeTooHighException();
}

Bureaucrat::Bureaucrat(const Bureaucrat & copy)
{ *this = copy; }

Bureaucrat& Bureaucrat::operator=(const Bureaucrat & copy)
{
	(std::string) this->_name = copy.getName();
	this->_grade = copy.getGrade();
	return (*this);
}

Bureaucrat::~Bureaucrat(void)
{ }

void Bureaucrat::upGrade(void)
{
	if (this->_grade > 1)
		this->_grade--;
}

void Bureaucrat::downGrade(void)
{
	if (this->_grade < 150)
		this->_grade++;
}

std::string	Bureaucrat::getName(void) const
{ return ((std::string) this->_name); }

int	Bureaucrat::getGrade(void) const
{ return (this->_grade); }

std::ostream&	operator<<(std::ostream & out, const Bureaucrat * target)
{
	out << target->getName() << ", bureaucrat grade " << target->getGrade();
	return (out);
}
