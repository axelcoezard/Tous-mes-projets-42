/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:29:27 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/29 17:20:33 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include "Form.hpp"

class RobotomyRequestForm : public Form
{
	private:
		std::string _target;
	public:
		RobotomyRequestForm(std::string target);
		RobotomyRequestForm(const RobotomyRequestForm & copy);
		~RobotomyRequestForm(void);

		void	execute(const Bureaucrat & executor) const;
		RobotomyRequestForm	*clone(std::string target) const;

		std::string	getTarget(void) const;
		void	setTarget(std::string & target);
};
