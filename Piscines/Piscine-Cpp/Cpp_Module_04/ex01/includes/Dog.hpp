/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:24:40 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/14 13:26:14 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
	private:
		Brain	*_brain;
	public:
		Dog(void);
		Dog(const Dog & copy);
		Dog&	operator=(const Dog & copy);
		virtual ~Dog(void);

		void	makeSound(void) const;

		Brain	*getBrain(void) const;
		void	setBrain(Brain *brain);
};

