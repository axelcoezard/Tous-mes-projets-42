/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 08:52:47 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/13 09:11:25 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int	main(void)
{
	ClapTrap	axel("Axel");
	ClapTrap	andrew("Andrew");

	axel.attack(andrew.getName());
	andrew.takeDamage(axel.getHitPoints());
	andrew.beRepaired(10);
	andrew.takeDamage(axel.getHitPoints());
	andrew.beRepaired(10);
	return (0);
}
