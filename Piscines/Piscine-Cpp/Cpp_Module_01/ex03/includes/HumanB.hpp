/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:11:46 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/09 12:19:07 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "Weapon.hpp"

class HumanB
{
	private:
		std::string	_name;
		Weapon	*	_weapon;
	public:
		HumanB(std::string name);
		void	attack(void);
		void	setWeapon(Weapon & weapon);
		~HumanB(void);
};

