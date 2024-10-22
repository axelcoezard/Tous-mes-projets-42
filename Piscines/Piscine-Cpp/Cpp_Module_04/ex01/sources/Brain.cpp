/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 11:48:20 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/14 12:27:35 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain(void)
{
	std::cout << "Brain default constructor called" << std::endl;
}

Brain::Brain(const Brain & copy)
{
	*this = copy;
	std::cout << "Brain copy constructor called" << std::endl;
}

Brain&	Brain::operator=(const Brain & copy)
{
	for (int i = 0; i < IDEAS_COUNT; i++)
		this->setIdea(i, copy.getIdea(i));
	std::cout << "Brain assignation operator called" << std::endl;
	return (*this);
}

Brain::~Brain(void)
{
	std::cout << "Brain default destructor called" << std::endl;
}

std::string	Brain::getIdea(int i) const
{
	if (i < IDEAS_COUNT)
		return (this->_ideas[i]);
	return (NULL);
}

void	Brain::setIdea(int i, std::string idea)
{
	if (i < IDEAS_COUNT)
		this->_ideas[i] = idea;
}
