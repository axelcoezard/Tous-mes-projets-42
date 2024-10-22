/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:31:13 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/14 15:45:27 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AMateria.hpp"
#include "ICharacter.hpp"

class Ice : public AMateria
{
	public:
		Ice(void);
		Ice(const Ice & copy);
		Ice&	operator=(const Ice & copy);
		virtual ~Ice(void);

		Ice*	clone(void) const;
		void	use(ICharacter& target);
};
