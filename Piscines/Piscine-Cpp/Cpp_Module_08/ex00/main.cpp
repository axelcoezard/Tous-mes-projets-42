/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 14:20:33 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/31 14:51:57 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include "easyfind.hpp"

int main(void)
{
	int ints[10] = {5, 6, 3, 2, 4, 1, 8, 7, 9, 0};
	
	std::vector<int> values;
	values.assign(ints, ints + 10);	
	
	try {
		std::cout << "Pos: " << easyfind(values, 8) << "\n";	
	} catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	
	try {
		easyfind(values, 72);	
	} catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}

	return (0);
}

