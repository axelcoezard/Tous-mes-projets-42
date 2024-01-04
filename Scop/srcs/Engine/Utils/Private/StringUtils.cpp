/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:56:35 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/07 11:36:35 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StringUtils.h"

bool StringUtils::EndsWith(const std::string& str, const std::string& suffix) {
	return str.size() >= suffix.size() && 0 == str.compare(str.size()-suffix.size(), suffix.size(), suffix);
}

bool StringUtils::StartsWith(const std::string& str, const std::string& prefix) {
	return str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix);
}

std::vector<std::string> StringUtils::Split(const std::string input, const char& delimiter) {
	std::vector<std::string> elements;
	std::stringstream stream(input);
	std::string element;

	while (getline(stream, element, delimiter)) {
		elements.push_back(element);
	}

	return elements;
}
