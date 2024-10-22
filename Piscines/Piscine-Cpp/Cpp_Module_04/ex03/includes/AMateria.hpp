/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:13:09 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/14 15:47:04 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "ICharacter.hpp"

class ICharacter;

class AMateria
{
	protected:
		std::string	_type;
	public:
		AMateria(void);
		AMateria(const std::string & type);
		AMateria(const AMateria & copy);
		AMateria&	operator=(const AMateria & copy);
		virtual	~AMateria(void);

		void	setType(std::string type);
		const std::string&	getType(void) const;

		virtual	AMateria*	clone(void) const = 0;
		virtual void	use(ICharacter & target);
};
