/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:29:55 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/29 17:24:25 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(std::string target)
	: Form::Form("presidential pardon", 25, 5), _target(target)
{ }

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm & copy)
	: Form::Form(copy), _target(copy.getTarget())
{ }

PresidentialPardonForm::~PresidentialPardonForm(void)
{ }

void	PresidentialPardonForm::execute(const Bureaucrat & executor) const
{
	std::cout << "Perceuses loud sound\n";

	if (executor.getGrade() > this->getGradeToExec())
		throw Form::GradeTooLowException();
	if (!this->isSigned())
		throw Form::NotSignedException();

	std::cout << this->getTarget() << " has been forgiven by Zafod Beeblebrox!\n";
}

PresidentialPardonForm	*PresidentialPardonForm::clone(std::string target) const
{ return (new PresidentialPardonForm(target)); }

std::string	PresidentialPardonForm::getTarget(void) const
{ return (this->_target); }

void	PresidentialPardonForm::setTarget(std::string & target)
{ this->_target = target; }
