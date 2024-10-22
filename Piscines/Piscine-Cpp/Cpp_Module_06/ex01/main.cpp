/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:32:02 by acoezard          #+#    #+#             */
/*   Updated: 2022/01/03 13:22:14 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

typedef struct
{
	std::string	name;
}	Data;

uintptr_t	serialize(Data* ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data *	deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data *>(raw));
}

int main(void)
{
	Data data = {"Axel"};
	std::cout << "Data addr: " << &data << std::endl; 
	std::cout << "Data name: " << data.name << std::endl; 

	uintptr_t raw = serialize(&data);
	std::cout << "Raw addr: " << &raw << std::endl; 
	std::cout << "Raw value: " << raw << std::endl; 

	Data	*dataBis = deserialize(raw);
	std::cout << "Deserialized data addr: " << dataBis << std::endl; 
	std::cout << "Deserialized data value: " << dataBis->name << std::endl; 
	return (0);
}

