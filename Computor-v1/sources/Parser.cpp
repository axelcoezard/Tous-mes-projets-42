/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:21:38 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/20 11:10:03 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv1.h"

void Parser::SkipAllSpaces(char*& str) {
	while (*str != 0 && std::isspace(*str)) {
		str++;
	}
}

int Parser::GetAdd(char*& str) {
	int ret = 0;

	Parser::SkipAllSpaces(str);
	if (*str == '+') { ret = 1; }
	if (*str == '-') { ret = -1; }
	if (ret != 0) { ++str; }

	return ret;
}

double Parser::GetDouble(char*& str, bool strict) {
	char* end;
	double value;

	Parser::SkipAllSpaces(str);
	value = std::strtod(str, &end);
	if (strict) {
		ASSERT(end == str, "Expected to find a double")
	} else if (end == str) {
		value = 1.0f;
	}

	str = end;
	return value;
}

long Parser::GetExponent(char*& str, bool strict) {
	char* end;
	long exponent;

	Parser::SkipAllSpaces(str);
	if (strict) {
		ASSERT(*str != '*', "Expected to find '*'")
		Parser::SkipAllSpaces(++str);

		ASSERT(*str != 'X' && *str != 'x', "Expected to find 'X' or 'x'")
		Parser::SkipAllSpaces(++str);

		ASSERT(*str != '^', "Expected to find '^'")
		Parser::SkipAllSpaces(++str);

		exponent = std::strtol(str, &end, 10);
		ASSERT(str == end, "Expected to find a long")
		ASSERT(exponent < 0, "Expected to find a positive power")
		str = end;
		return exponent;
	}

	if (*str == '*') {
		Parser::SkipAllSpaces(++str);
	}

	if (*str == 'X' || *str == 'x') {
		Parser::SkipAllSpaces(++str);

		if (*str == '^') {
			Parser::SkipAllSpaces(++str);

			exponent = std::strtol(str, &end, 10);
			ASSERT(str == end, "Expected to find a long")
			ASSERT(exponent < 0, "Expected to find a positive power")
			str = end;
			return exponent;
		}

		exponent = std::strtol(str, &end, 10);
		ASSERT(str != end, "Didn't expected to find a long")

		return 1L;
	}
	return 0L;
}

void Parser::ParseSide(char*& str, Polynom& side, bool strict) {
	int sign = 1;
	do {
		double coeff = Parser::GetDouble(str, strict);
		long exponent = Parser::GetExponent(str, strict);

		side.Add(exponent, coeff * (double) sign);
	} while ((sign = Parser::GetAdd(str)) != 0);
}

void Parser::Parse(char*& str, Polynom& polynom, bool strict) {
	Polynom left, right;

	Parser::ParseSide(str, left, strict);
	ASSERT(*str != '=', "Expected to find '='")
	Parser::ParseSide(++str, right, strict);

	for (long i = 0; i <= fmax(left.Degree(), right.Degree()); i++) {
		if (left[i] - right[i] != 0.0) {
			polynom.Add(i, left[i] - right[i]);
		}
	}
}
