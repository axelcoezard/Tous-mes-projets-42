/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:24:13 by acoezard          #+#    #+#             */
/*   Updated: 2022/01/03 14:14:53 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class Base
{
	public:
		virtual ~Base(void) {};
};

class A: public Base {};
class B: public Base {};
class C: public Base {};

Base *	generate(void);
void	identify(Base * p);
void	identify(Base & p);
