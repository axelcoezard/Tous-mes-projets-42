/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Formm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:17:23 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/21 12:15:58 by acoezard         ###   ########.fr       */
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
		Form(void);
		Form(std::string name, int gradeToSign, int gradeToExec);
		Form(const Form & copy);
		~Form(void);

		Form&		beSigned(Bureaucrat &author);
		
		std::string	getName(void) const;
		int			getGradeToSign(void) const;
		int			getGradeToExec(void) const;
		bool		isSigned(void) const;

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
};

std::ostream&	operator<<(std::ostream & out, const Form *target);
