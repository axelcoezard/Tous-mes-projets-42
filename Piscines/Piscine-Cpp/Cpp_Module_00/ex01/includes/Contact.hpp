/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:57:49 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/08 13:50:15 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class Contact
{
	private:
		std::string	_firstname;
		std::string	_lastname;
		std::string	_nickname;
		std::string _phone_number;
		std::string	_darkest_secret;
	public:
		Contact(void);
		void		set_firstname(std::string firstname);
		void		set_lastname(std::string lastname);
		void		set_nickname(std::string nickname);
		void		set_phone_number(std::string phone_number);
		void		set_darkest_secret(std::string darkest_secret);
		std::string	get_firstname(void);
		std::string	get_lastname(void);
		std::string	get_nickname(void);
		std::string	get_phone_number(void);
		std::string	get_darkest_secret(void);
		~Contact(void);
};
