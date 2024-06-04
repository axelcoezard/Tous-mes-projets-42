/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Console.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:11:21 by acoezard          #+#    #+#             */
/*   Updated: 2024/01/23 22:13:14 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

namespace Console
{
	static std::string GREEN = "\033[1;32m";
	static std::string BLUE = "\033[1;36m";
	static std::string RED = "\x1b[31m";
	static std::string PURPLE = "\x1b[35m";

	static std::string IBLUE = "\x1b[44m";
	static std::string IGREEN = "\x1b[42m";
	static std::string IRED = "\x1b[41m";

	static std::string RESET = "\033[0m";

	void Print(std::string type, std::string str, std::string color);
	void Log(std::string str);
	void Error(std::string str);
}
