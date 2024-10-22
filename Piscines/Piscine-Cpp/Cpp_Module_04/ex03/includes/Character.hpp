/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:20:56 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/14 15:42:34 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ICharacter.hpp"

class Character : public ICharacter
{
	private:
		std::string	_name;
		AMateria	*_inventory[4];
	public:
		Character(void);
		Character(std::string name);
		Character(const Character & copy);
		Character&	operator=(const Character & copy);
		~Character(void);

		void	equip(AMateria *m);
		void	unequip(int i);
		void	use(int i, ICharacter& target);

		void	setName(std::string name);
		const std::string&	getName(void) const;
		void	setMateria(int i, AMateria *m);
		AMateria*	getMateria(int i) const;
};
