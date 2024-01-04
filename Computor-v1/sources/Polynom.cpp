/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Polynom.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:45:31 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/20 11:36:30 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv1.h"

Polynom::Polynom(void): m_degree(0) {}

void Polynom::Add(long exponent, double value) {
	std::map<long, double>::iterator it = m_terms.find(exponent);

	if (it != m_terms.end()) {
		it->second += value;
	} else {
		m_terms.insert(std::pair<long, double>(exponent, value));
	}

	if (m_degree < exponent) {
		m_degree = exponent;
	}
}

double Polynom::operator[](long exponent) {
	std::map<long, double>::iterator it = m_terms.find(exponent);
	if (it == m_terms.end()) {
		return 0;
	}
	return m_terms.at(exponent);
}

long Polynom::Degree(void) {
	return m_degree;
}

std::ostream& operator<<(std::ostream& os, Polynom& polynom) {
	bool first = true;

	for (int i = 0; i <= polynom.Degree(); i++) {
		int sign = 1;
		if (polynom[i] == 0) continue;

		if (!first) {
			if (polynom[i] < 0)	{ sign = -1; }
			if (sign == 1)		{ os << " + "; }
			else				{ os << " - "; }
		}

		os << sign * polynom[i];

		if (sign * polynom[i] != 1 && i > 0) { os << " * "; }
		if (i == 1)				{ os << "x"; }
		if (i > 1)				{ os << "x^" << i; }

		first = false;
	}
	return os;
}
