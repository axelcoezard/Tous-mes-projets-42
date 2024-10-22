/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:22:22 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/08 20:20:43 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class Zombie
{
	private:
		std::string	_name;
	public:
		Zombie();
		void	announce(void);
		void	setName(std::string name);
		~Zombie(void);
};

Zombie*	zombieHorde(int N, std::string name);
