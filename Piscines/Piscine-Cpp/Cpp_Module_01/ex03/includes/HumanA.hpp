/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:11:49 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/09 12:19:16 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "Weapon.hpp"

class HumanA
{
	private:
		std::string	_name;
		Weapon	*	_weapon;
	public:
		HumanA(std::string name, Weapon & weapon);
		void	attack(void);
		~HumanA(void);
};
