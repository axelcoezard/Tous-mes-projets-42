/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replace.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:51:52 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/09 14:50:38 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>

class Replace
{
	private:
		std::ifstream	_file;
		std::ofstream	_out_file;
		std::string		_filename;
	public:
		Replace(void);
		bool	setFilename(std::string filename);
		bool	replace(std::string s1, std::string s2);
		~Replace(void);
};
