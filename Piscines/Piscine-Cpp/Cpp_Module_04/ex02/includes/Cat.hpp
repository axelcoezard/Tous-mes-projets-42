/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:23:30 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/14 13:26:08 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
	private:
		Brain	*_brain;
	public:
		Cat(void);
		Cat(const Cat & copy);
		Cat&	operator=(const Cat & copy);
		virtual ~Cat(void);

		void	makeSound(void) const;

		Brain	*getBrain(void) const;
		void	setBrain(Brain *brain);
};
