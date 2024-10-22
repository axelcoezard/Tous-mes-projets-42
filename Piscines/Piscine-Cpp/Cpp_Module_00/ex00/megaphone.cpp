/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:05:22 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/30 13:51:48 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

/**
 * @brief	La fonction yell crie la phrase choisie.
 * @param	sentence La phrase a crier.
 */
void	yell(std::string sentence)
{
	int	length = sentence.length();

	for (int j = 0 ; j < length ; j++)
		std::cout << (char) std::toupper(sentence[j]);
}

/**
 * @brief	Ce programme ecrit en majuscule dans le terminal
 * 			toutes les phrases passees en argument.
 * @param	ac	Le nombre d'arguments.
 * @param	av	Les arguments.
 * @return	0 dans tous les cas.
 */
int	main(int ac, char **av)
{
	if (ac == 1)
		yell("* LOUD AND UNBEARABLE FEEDBACK NOISE *");
	else
		for (int i = 1; i < ac; i++)
			yell(std::string(av[i]));
	std::cout << std::endl;
	return (0);
}
