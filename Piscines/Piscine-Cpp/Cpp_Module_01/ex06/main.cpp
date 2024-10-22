/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:11:28 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/09 18:01:02 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Karen.hpp"

int	levelToInteger(std::string level)
{
	if (level == "DEBUG")	return (DEBUG);
	if (level == "INFO")	return (INFO);
	if (level == "WARNING")	return (WARNING);
	if (level == "ERROR")	return (ERROR);
	return (NONE);
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		Karen	karen;

		switch (levelToInteger(av[1]))
		{
		case DEBUG:
			std::cout << "[ DEBUG ]\n";
			karen.complain("DEBUG");
			std::cout << std::endl;
		case INFO:
			std::cout << "[ INFO ]\n";
			karen.complain("INFO");
			std::cout << std::endl;
		case WARNING:
			std::cout << "[ WARNING ]\n";
			karen.complain("WARNING");
			std::cout << std::endl;
		case ERROR:
			std::cout << "[ ERROR ]\n";
			karen.complain("ERROR");
			break;
		default:
			std::cout << "[ Probably complaining about insignificant problems ]\n";
			break;
		}
	}
	return (0);
}
