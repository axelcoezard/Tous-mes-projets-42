#pragma once

#include <vector>
#include <string>
#include <sstream>

namespace Utils
{
	std::vector<std::string> str_split(std::string str, std::string delimiters);

	std::string str_ltrim(std::string str, const char* charset);
	std::string str_rtrim(std::string str, const char* charset);
	std::string str_trim(std::string str, const char* charset);

	std::string str_toupper(std::string str);
	std::string str_tolower(std::string str);
}
