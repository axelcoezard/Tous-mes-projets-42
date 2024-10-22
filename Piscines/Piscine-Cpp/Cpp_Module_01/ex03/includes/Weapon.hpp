/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:11:51 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/09 12:23:51 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class Weapon
{
	private:
		std::string	_type;
	public:
		Weapon(std::string type);
		const std::string	& getType(void);
		void	setType(std::string type);
		~Weapon(void);
};
