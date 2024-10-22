/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:29:21 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/30 14:36:50 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact(void) { }

void	Contact::set_firstname(std::string firstname)
{ this->_firstname = firstname; }

std::string	Contact::get_firstname(void)
{ return (this->_firstname); }

void	Contact::set_lastname(std::string lastname)
{ this->_lastname = lastname; }

std::string	Contact::get_lastname(void)
{ return (this->_lastname); }

void	Contact::set_nickname(std::string nickname)
{ this->_nickname = nickname; }

std::string	Contact::get_nickname(void)
{ return (this->_nickname); }

void	Contact::set_phone_number(std::string phone_number)
{ this->_phone_number = phone_number; }

std::string	Contact::get_phone_number(void)
{ return (this->_phone_number); }

void	Contact::set_darkest_secret(std::string darkest_secret)
{ this->_darkest_secret = darkest_secret; }

std::string	Contact::get_darkest_secret(void)
{ return (this->_darkest_secret); }

Contact::~Contact(void) { }
