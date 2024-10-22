/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringUtils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:55:07 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/07 10:28:10 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string.h>
#include <string>
#include <vector>
#include <sstream>

namespace StringUtils {
	bool EndsWith(const std::string& str, const std::string& suffix);
	bool StartsWith(const std::string& str, const std::string& prefix);
	//std::vector<std::string> Split(std::string str, std::string delimiters);
	std::vector<std::string> Split(const std::string input, const char& delimiter);
}
