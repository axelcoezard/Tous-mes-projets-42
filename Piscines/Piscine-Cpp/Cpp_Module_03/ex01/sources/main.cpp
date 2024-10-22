/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 08:52:47 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/13 11:49:44 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int	main(void)
{
	ScavTrap	axel("Axel");
	ClapTrap	andrew("Andrew");

	axel.attack(andrew.getName());
	andrew.takeDamage(axel.getHitPoints());
	andrew.beRepaired(10);
	axel.guardGate();
	return (0);
}
