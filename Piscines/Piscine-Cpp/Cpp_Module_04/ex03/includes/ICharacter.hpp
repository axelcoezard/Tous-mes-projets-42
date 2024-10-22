/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICharacter.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:17:01 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/14 16:04:53 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "AMateria.hpp"

class AMateria;

class ICharacter
{
	public:
		virtual	~ICharacter(void) {}

		virtual void	equip(AMateria* m) = 0;
		virtual void	unequip(int i) = 0;
		virtual void	use(int i, ICharacter& target) = 0;

		virtual void	setName(std::string name) = 0;
		virtual const std::string&	getName(void) const = 0;
		virtual void	setMateria(int i, AMateria *m) = 0;
		virtual AMateria*	getMateria(int i) const = 0;
};
