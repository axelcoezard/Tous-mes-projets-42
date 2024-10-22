/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:17:49 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/09 12:24:10 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string type)
{ this->setType(type); }

const std::string	& Weapon::getType(void)
{ return (this->_type); }

void	Weapon::setType(std::string type)
{ this->_type = type; }

Weapon::~Weapon(void)
{ }
