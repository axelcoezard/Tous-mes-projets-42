/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:48:42 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/14 14:07:21 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main(void)
{
	// Instancier la class Animal empechera la compilation
	// const Animal	*animal = new Animal();

	const Dog	*dog = new Dog();
	const Cat	*cat = new Cat();

	dog->makeSound();
	cat->makeSound();

	delete cat;
	delete dog;

	return (0);
}

