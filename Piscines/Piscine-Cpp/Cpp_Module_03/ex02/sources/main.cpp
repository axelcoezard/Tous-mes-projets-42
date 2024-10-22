/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 08:52:47 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/13 12:08:36 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int	main(void)
{
	ScavTrap	axel("Axel");
	FragTrap	raph("raph");
	ClapTrap	andrew("Andrew");

	axel.attack(raph.getName());
	raph.takeDamage(axel.getHitPoints());
	raph.beRepaired(10);
	axel.guardGate();
	raph.beRepaired(10);
	andrew.attack(axel.getName());
	axel.takeDamage(andrew.getHitPoints());
	raph.highFivesGuys();
	return (0);
}
