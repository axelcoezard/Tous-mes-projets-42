/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:01:30 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/29 17:31:47 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern
{
	private:
		Form	**types;
	public:
		Intern(void);
		Intern(const Intern & copy);
		~Intern(void);

		Form	*makeForm(std::string formName, std::string formTarget);
		
		class FormDoesNotExistException : std::exception {
			public:
				const char	*what(void) const throw() {
					return ("Form Does Not Exist");
				}
		};
};
