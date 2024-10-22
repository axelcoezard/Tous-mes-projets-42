/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 11:36:56 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/14 12:27:41 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

#define	IDEAS_COUNT	100

class Brain
{
	protected:
		std::string	_ideas[IDEAS_COUNT];
	public:
		Brain(void);
		Brain(const Brain & copy);
		Brain &	operator=(const Brain & copy);
		~Brain(void);

		std::string	getIdea(int i) const;
		void		setIdea(int i, std::string idea);
};
