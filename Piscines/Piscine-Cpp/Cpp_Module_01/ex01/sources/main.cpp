/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:28:25 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/08 20:28:51 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Zombie.hpp"

int main(void)
{
	std::string	hordeName = "Axel";
	int			hordeSize = 9;

	Zombie	*horde = zombieHorde(
		hordeSize, hordeName
	);

	for (int i = 0; i < hordeSize; i++)
		(horde + i)->announce();
	delete[] horde;
}
