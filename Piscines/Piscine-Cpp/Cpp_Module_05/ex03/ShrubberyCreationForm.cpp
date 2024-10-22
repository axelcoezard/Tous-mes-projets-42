/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:28:20 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/29 17:24:09 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string target)
	: Form::Form("shrubbery creation", 145, 137), _target(target)
{ }

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm & copy)
	: Form::Form(copy), _target(copy.getTarget())
{ }

ShrubberyCreationForm::~ShrubberyCreationForm(void)
{ }

void	ShrubberyCreationForm::execute(const Bureaucrat & executor) const
{
	std::fstream file;
	
	if (executor.getGrade() > this->getGradeToExec())
		throw Form::GradeTooLowException();
	if (!this->isSigned())
		throw Form::NotSignedException();

	file.open(this->getTarget() + "_shrubbery", std::ios::out);
	file << "   w     w\n  www   www\n wwwww wwwww\n   w     w\n";
	file.close();
}

ShrubberyCreationForm	*ShrubberyCreationForm::clone(std::string target) const
{ return (new ShrubberyCreationForm(target)); }

std::string	ShrubberyCreationForm::getTarget(void) const
{ return (this->_target); }

void	ShrubberyCreationForm::setTarget(std::string & target)
{ this->_target = target; }
