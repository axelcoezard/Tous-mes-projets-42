/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:54:21 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/09 14:33:55 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>

#include "Phonebook.hpp"
#include "Contact.hpp"

static void _begin(void)
{
	std::cout << "=================================================\n";
	std::cout << "            BIENVENUE SUR LE PHONEBOOK           \n";
	std::cout << std::endl;
	std::cout << "                    Commandes:                   \n";
	std::cout << "                ADD | SEARCH | EXIT              \n";
	std::cout << "=================================================\n";
}

static void	_add(Phonebook & phonebook)
{
	std::string	entry;
	Contact	* contact = new Contact();

	if (std::cin.eof()) return ;
	std::cout << "phonebook: firstname=";
	std::getline(std::cin, entry);
	contact->set_firstname(entry);
	if (std::cin.eof()) return ;
	std::cout << "phonebook: lastname=";
	std::getline(std::cin, entry);
	contact->set_lastname(entry);
	if (std::cin.eof()) return ;
	std::cout << "phonebook: nickname=";
	std::getline(std::cin, entry);
	contact->set_nickname(entry);
	if (std::cin.eof()) return ;
	std::cout << "phonebook: phone_number=";
	std::getline(std::cin, entry);
	contact->set_phone_number(entry);
	if (std::cin.eof()) return ;
	std::cout << "phonebook: darkest_secret=";
	std::getline(std::cin, entry);
	contact->set_darkest_secret(entry);
	phonebook += contact;
}

static void	_show(Contact * contact)
{
	std::cout << "=================================================\n";
	std::cout << "firstname=" << contact->get_firstname() << std::endl;
	std::cout << "lastname=" << contact->get_lastname() << std::endl;
	std::cout << "nickname=" << contact->get_nickname() << std::endl;
	std::cout << "phone_number=" << contact->get_phone_number() << std::endl;
	std::cout << "darkest_secret=" << contact->get_darkest_secret() << std::endl;
	std::cout << "=================================================\n";
}

static std::string	_trim(std::string s)
{
	if (s.length() >= 10)
		s = s.substr(0, 9).append(".");
	return (s);
}

static void _search(Phonebook & phonebook)
{
	std::cout << "=================================================\n";
	std::cout << "     index | first name |  last name |   nickname\n";
	std::cout << "-------------------------------------------------\n";
	if (phonebook.get_size() > 0)
		for (int i = 0; i < 8; i++)
		{
			if (phonebook[i] == NULL)
				continue;
			Contact * c = phonebook[i];
			std::cout << std::setw(10) << (i + 1);
			std::cout << " | ";
			std::cout << std::setw(10) << _trim(c->get_firstname());
			std::cout << " | ";
			std::cout << std::setw(10) << _trim(c->get_lastname());
			std::cout << " | ";
			std::cout << std::setw(10) << _trim(c->get_nickname());
			std::cout << std::endl;
		}
	else
		std::cout << "            Aucun contact enregistre             \n";
	std::cout << "=================================================\n";
	std::string	entry;
	std::cout << "phonebook: id=";
	std::getline(std::cin, entry);
	int id = atoi(entry.c_str());
	if (id >=1 && id <= 8 && phonebook[id - 1])
		_show(phonebook[id - 1]);
}

int	main(void)
{
	Phonebook	phonebook;
	std::string	entry;

	_begin();
	while (!std::cin.eof())
	{
		std::cout << "phonebook$ ";
		std::getline(std::cin, entry);
		if (entry == "ADD")
			_add(phonebook);
		if (entry == "SEARCH")
			_search(phonebook);
		if (entry == "EXIT")
			break;
	}
	return (0);
}
