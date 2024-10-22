/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 08:52:47 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/13 15:10:50 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"

int	main(void)
{
	DiamondTrap	loan("Loan");
	ScavTrap	axel("Axel");
	FragTrap	raph("Raphael");
	ClapTrap	andrew("Andrew");

	loan.attack(raph.getName());
	raph.takeDamage(loan.getHitPoints());
	axel.attack(raph.getName());
	axel.attack(loan.getName());
	raph.takeDamage(axel.getHitPoints());
	loan.takeDamage(axel.getHitPoints());
	raph.beRepaired(10);
	axel.guardGate();
	andrew.attack(axel.getName());
	axel.takeDamage(andrew.getHitPoints());
	raph.highFivesGuys();
	loan.whoAmI();
	return (0);
}
