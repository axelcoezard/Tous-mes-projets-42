/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Karen.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:12:14 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/09 17:56:18 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

#define	NONE	0
#define DEBUG	1
#define	INFO	2
#define WARNING	3
#define ERROR	4

class Karen
{
	private:
		std::string	_keys[4];
		void (Karen::*_fcts[4])(void);

		void	debug(void);
		void	info(void);
		void	warning(void);
		void	error(void);
	public:
		Karen(void);
		void	complain(std::string level);
		~Karen(void);
};
