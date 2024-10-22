/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replace.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:59:57 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/09 15:08:42 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Replace.hpp"

Replace::Replace(void)
{ }

bool	Replace::setFilename(std::string filename)
{
	if (filename.empty())
		return (false);
	this->_filename = filename;
	if (this->_file.is_open())
		this->_file.close();
	this->_file.open(filename);
	return (true);
}

bool	Replace::replace(std::string s1, std::string s2)
{
	if (s1.empty() || s2.empty())
		return (false);
	// On charge le contenu du fichier source
	std::string	result;
	result.assign(
		std::istreambuf_iterator<char>(this->_file),
		std::istreambuf_iterator<char>()
	);
	// On remplace tous les s1 par s2
	size_t	length = s1.length();
	for (size_t pos = 0; pos < result.length(); pos++)
		if (result.compare(pos, length, s1) == 0)
			result.erase(pos, length).insert(pos, s2);
	// On ecrit le resultat dans le fichier de destination
	std::string	out_filename = this->_filename;
	std::transform(
		out_filename.begin(), out_filename.end(),
		out_filename.begin(), ::toupper
	);
	this->_out_file.open(out_filename + ".replace");
	this->_out_file << result;
	this->_out_file.close();
	return (true);
}

Replace::~Replace(void)
{
	if (this->_file.is_open())
		this->_file.close();
}
