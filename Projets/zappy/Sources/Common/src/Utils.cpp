#include "Utils.hpp"

std::vector<std::string> Utils::str_split(std::string str, std::string delimiters)
{
	std::vector<std::string> parts;
	size_t pos_start = 0;
	size_t pos_end;

	while ((pos_end = str.find(delimiters, pos_start)) != std::string::npos)
	{
		std::string local = str.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delimiters.length();
		parts.push_back(local);
	}

	parts.push_back(str.substr(pos_start));
	return parts;
}

std::string Utils::str_ltrim(std::string str, const char* charset)
{
	str.erase(0, str.find_first_not_of(charset));
	return str;
}

std::string Utils::str_rtrim(std::string str, const char* charset)
{
	str.erase(str.find_last_not_of(charset) + 1);
	return str;
}

std::string Utils::str_trim(std::string str, const char* charset)
{
	return str_ltrim(str_rtrim(str, charset), charset);
}

std::string Utils::str_toupper(std::string str)
{
	std::stringstream ss;
	for (size_t i = 0; i < str.size(); i++)
		ss << (char) std::toupper(str[i]);
	return ss.str();
}

std::string Utils::str_tolower(std::string str)
{
	std::stringstream ss;
	for (size_t i = 0; i < str.size(); i++)
		ss << (char) std::tolower(str[i]);
	return ss.str();
}