/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:05:45 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/15 09:44:07 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IMateriaSource.hpp"
#include "AMateria.hpp"

class MateriaSource : public IMateriaSource
{
	private:
		AMateria	*_learned[4];
	public:
		MateriaSource(void);
		MateriaSource(const MateriaSource & copy);
		MateriaSource&	operator=(const MateriaSource & copy);
		~MateriaSource(void);

		void	learnMateria(AMateria* m);
		AMateria*	createMateria(std::string const & type);

		void	setMateria(int i, AMateria	*m);
		AMateria	*getMateria(int i) const;
};
