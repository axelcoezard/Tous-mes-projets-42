/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:48:58 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/15 15:27:28 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stdexcept>

class Bureaucrat
{
	private:
		const std::string	_name;
		int					_grade;
	public:
		Bureaucrat(void);
		Bureaucrat(std::string name, int grade);
		Bureaucrat(const Bureaucrat & copy);	
		Bureaucrat&	operator=(const Bureaucrat & copy);
		~Bureaucrat(void);

		void	upGrade(void);
		void	downGrade(void);

		std::string	getName(void) const;
		int			getGrade(void) const;

		class GradeTooHighException : std::exception {
			public:
				const char	*what(void) const throw() {
					return ("Error: Grade Too High");
				}
		};
		class GradeTooLowException : std::exception {
			public:
				const char	*what(void) const throw() {
					return ("Error: Grade Too Low");
				}
		};
};

std::ostream&	operator<<(std::ostream & out, const Bureaucrat * target);
