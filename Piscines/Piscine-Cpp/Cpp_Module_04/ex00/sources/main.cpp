/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:58:00 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/15 11:33:18 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int	main(void)
{
	std::cout << "------ NORMAL PART ------" << std::endl;
	const Animal* meta = new Animal();
	const Animal* dog = new Dog();
	const Animal* cat = new Cat();

	std::cout << meta->getType() << " " << std::endl;
	std::cout << dog->getType() << " " << std::endl;
	std::cout << cat->getType() << " " << std::endl;

	meta->makeSound();
	dog->makeSound();
	cat->makeSound();

	delete cat;
	delete dog;
	delete meta;

	std::cout << "\n------ WRONG PART -------" << std::endl;
	const WrongAnimal* wmeta = new WrongAnimal();
	const WrongAnimal* wcat = new WrongCat();

	std::cout << wmeta->getType() << " " << std::endl;
	std::cout << wcat->getType() << " " << std::endl;

	wmeta->makeSound();
	wcat->makeSound();

	delete wcat;
	delete wmeta;

	return (0);
}

