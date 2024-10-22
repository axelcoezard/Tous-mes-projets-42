/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:28:49 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/29 17:20:47 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include "Form.hpp"

class ShrubberyCreationForm : public Form
{
	private:
		std::string _target;
	public:
		ShrubberyCreationForm(std::string target);
		ShrubberyCreationForm(const ShrubberyCreationForm & copy);
		~ShrubberyCreationForm(void);

		void	execute(const Bureaucrat & executor) const;
		ShrubberyCreationForm	*clone(std::string target) const;

		std::string	getTarget(void) const;
		void	setTarget(std::string & target);
};
