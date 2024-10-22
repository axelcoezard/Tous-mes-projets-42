/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:42:00 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/09 17:36:56 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.hpp"

Phonebook::Phonebook(void)
{
	this->_limit = 8;
	this->_size = 0;
	for (int i = 0; i < this->_limit; i++)
		this->_contacts[i] = NULL;
}

int		Phonebook::get_size(void)
{ return (this->_size); }

void	Phonebook::operator+=(Contact * contact)
{
	if (this->_size + 1 <= this->_limit)
		this->_contacts[this->_size++] = contact;
}

Contact * Phonebook::operator[](int index)
{ return (this->_contacts[index]); }

Phonebook::~Phonebook(void)
{ }
