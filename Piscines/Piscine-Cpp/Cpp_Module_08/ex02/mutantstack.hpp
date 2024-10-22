/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutantstack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:49:38 by acoezard          #+#    #+#             */
/*   Updated: 2022/01/04 13:19:30 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stack>
#include <algorithm>

template <typename T>
class MutantStack : public std::stack<T>
{
	public:
		MutantStack(void) : std::stack<T>()
		{ }

		MutantStack(const MutantStack & copy) : std::stack<T>(copy)
		{ *this = copy; }

		~MutantStack(void)
		{ }

		MutantStack&	operator=(const MutantStack & copy)
		{
			std::stack<T>::operator=(copy);
			return (*this);
		}

		typedef typename std::stack<T>::container_type::iterator iterator; 
		
		iterator	begin(void)
		{
			return (this->c.begin());
		}

		iterator	end(void)
		{
			return (this->c.end());
		}
};
