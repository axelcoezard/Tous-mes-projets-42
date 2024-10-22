/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:30:47 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/29 15:54:57 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form(std::string name, int gradeToSign, int gradeToExec)
	: _name(name), _signed(false), _gradeToSign(gradeToSign), _gradeToExec(gradeToExec)
{
	if (this->_gradeToSign > 150)
		throw Bureaucrat::GradeTooHighException(); 
	if (this->_gradeToSign < 1)
		throw Bureaucrat::GradeTooLowException();
	if (this->_gradeToExec > 150)
		throw Bureaucrat::GradeTooHighException(); 
	if (this->_gradeToExec < 1)
		throw Bureaucrat::GradeTooLowException();
}

Form::Form(const Form & copy)
	: _name(copy.getName()),
	  _gradeToSign(copy.getGradeToSign()),
	  _gradeToExec(copy.getGradeToExec())
{ this->_signed = copy.isSigned(); }

Form::~Form(void)
{ }

Form&	Form::beSigned(Bureaucrat &author)
{
	if (author.getGrade() > this->getGradeToSign())
		throw Form::GradeTooLowException();
	this->_signed = true;
	return (*this);
}
		
std::string	Form::getName(void) const
{ return ((std::string) this->_name); }

int	Form::getGradeToSign(void) const
{ return ((int) this->_gradeToSign); }

int	Form::getGradeToExec(void) const
{ return ((int) this->_gradeToExec); }

bool	Form::isSigned(void) const
{ return (this->_signed); }

std::ostream&	operator<<(std::ostream & out, const Form * form)
{
	out << form->getName() << ", form needs " << form->getGradeToSign();
	out << " grade to be signed and needs " << form->getGradeToExec();
	out << " grade to be executed. Signed: " << form->isSigned();
	return (out);
}
