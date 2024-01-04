/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computorv1.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:08:56 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/20 11:11:16 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <iostream>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(condition, error) if (condition) throw std::runtime_error(error);

struct Polynom {
	private:
		std::map<long, double> m_terms;
		long m_degree;
	public:
		Polynom(void);

		void Add(long exponent, double value);
		double operator[](long exponent);
		long Degree(void);
};

std::ostream& operator<<(std::ostream& os, Polynom& polynom);

namespace Parser {
	void SkipAllSpaces(char*& str);
	int GetAdd(char*& str);
	double GetDouble(char*& str, bool strict);
	long GetExponent(char*& str, bool strict);
	void ParseSide(char*& str, Polynom& polynom, bool strict);
	void Parse(char*& str, Polynom& polynom, bool strict);
};

namespace Solver {
	void Solve(Polynom& polynom);
	void Solve0(void);
	void Solve1(Polynom& polynom);
	void Solve2(Polynom& polynom);
};
