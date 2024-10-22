/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:58:00 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/14 13:35:12 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int	main(void)
{
	Animal	*animals[10];

	// On cree 10 chiens et 10 chats
	for (int i = 0; i < 5; i++)
		animals[i] = new Dog();
	for (int i = 5; i < 10; i++)
		animals[i] = new Cat();
	// On fait faire du bruit aux chiens et chats
	for (int i = 0; i < 10; i++)
		animals[i]->makeSound();
	// On supprime tous les animaux
	for (int i = 0; i < 10; i++)
		delete animals[i];

	return (0);
}

