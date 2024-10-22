/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:20:51 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/14 12:28:51 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class Animal
{
	protected:
		std::string	_type;
	public:
		Animal(void);
		Animal(const Animal & copy);
		Animal&	operator=(const Animal & copy);
		virtual ~Animal(void);

		virtual void	makeSound(void) const;

		std::string	getType(void) const;
		void		setType(std::string type);
};
