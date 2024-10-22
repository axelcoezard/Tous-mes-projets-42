/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:48:58 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/29 16:27:23 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stdexcept>
#include "Form.hpp"

class Form;

class Bureaucrat
{
	private:
		const std::string	_name;
		int					_grade;
	public:
		Bureaucrat(std::string name, int grade);
		Bureaucrat(const Bureaucrat & copy);	
		Bureaucrat&	operator=(const Bureaucrat & copy);
		~Bureaucrat(void);

		void	upGrade(void);
		void	downGrade(void);
		void	signForm(Form *form);
		void	executeForm(const Form & form);

		std::string	getName(void) const;
		int			getGrade(void) const;

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

std::ostream&	operator<<(std::ostream & out, const Bureaucrat *target);
