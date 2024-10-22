/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:57:02 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/09 11:07:33 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int	main(void)
{
	std::string	message = "HI THIS IS BRAIN";

	std::string	* stringPTR = &message;
	std::string	& stringREF = message;

	std::cout << "String address: " << &message << std::endl;

	std::cout << "StringPTR address: " << stringPTR << std::endl;
	std::cout << "StringREF address: " << &stringREF << std::endl;

	std::cout << "String value from StringPTR: " << *stringPTR << std::endl;
	std::cout << "String value from StringREF: " << stringREF << std::endl;
	return (0);
}
