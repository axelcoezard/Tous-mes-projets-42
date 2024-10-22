/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:30:10 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/29 17:20:42 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include "Form.hpp"

class PresidentialPardonForm : public Form
{
	private:
		std::string _target;
	public:
		PresidentialPardonForm(std::string target);
		PresidentialPardonForm(const PresidentialPardonForm & copy);
		~PresidentialPardonForm(void);

		void	execute(const Bureaucrat & executor) const;
		PresidentialPardonForm	*clone(std::string target) const;

		std::string	getTarget(void) const;
		void	setTarget(std::string & target);
};
