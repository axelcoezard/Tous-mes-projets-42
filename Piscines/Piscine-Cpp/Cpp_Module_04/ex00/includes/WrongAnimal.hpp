/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:20:51 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/15 11:03:21 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class WrongAnimal
{
	protected:
		std::string	_type;
	public:
		WrongAnimal(void);
		WrongAnimal(const WrongAnimal & copy);
		WrongAnimal&	operator=(const WrongAnimal & copy);
		~WrongAnimal(void);

		std::string	getType(void) const;
		void		setType(std::string type);

		void	makeSound(void) const;
};
