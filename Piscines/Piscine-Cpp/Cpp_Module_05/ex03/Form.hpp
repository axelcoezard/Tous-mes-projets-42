/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Formm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:17:23 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/29 17:27:35 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stdexcept>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
	private:
		const std::string _name;
		bool		_signed;
		const int	_gradeToSign;
		const int	_gradeToExec;
	public:
		Form(std::string name, int gradeToSign, int gradeToExec);
		Form(const Form & copy);
		virtual ~Form(void);

		Form&			beSigned(Bureaucrat &author);
		virtual void	execute(const Bureaucrat & executor) const = 0;
		
		virtual	Form	*clone(std::string target) const = 0;

		std::string	getName(void) const;
		int			getGradeToSign(void) const;
		int			getGradeToExec(void) const;
		bool		isSigned(void) const;

		virtual std::string	getTarget(void) const = 0;
		virtual void	setTarget(std::string & target) = 0;

		class GradeTooHighException : std::exception {
			public:
				const char	*what(void) const throw() {
					return ("Grade Too High");
				}
		};
		class GradeTooLowException : std::exception {
			public:
				const char	*what(void) const throw() {
					return ("Grade Too Low");
				}
		};
		class NotSignedException : std::exception {
			public:
				const char	*what(void) const throw() {
					return ("Form Not Signed");
				}
		};

};

std::ostream&	operator<<(std::ostream & out, const Form *target);
