/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 08:44:39 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/20 11:10:07 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv1.h"

void Solver::Solve(Polynom& polynom) {
	long degree = polynom.Degree();

	if (degree == 0) { return (void) Solver::Solve0(); }

	std::cout << "Reduced form: " << polynom << " = 0" << std::endl;
	std::cout << "Polynomial degree: " << polynom.Degree() << std::endl;

	if (degree == 1) { return (void) Solver::Solve1(polynom); }
	if (degree == 2) { return (void) Solver::Solve2(polynom); }

	if (degree > 2) {
		throw std::runtime_error("The polynomial degree is strictly greater than 2, I can't solve.");
	}
}

void Solver::Solve0(void) {
	return (void) (std::cout << "Each number in ℝ is a solution..." << std::endl);
}

void Solver::Solve1(Polynom& polynom) {
	double a = polynom[1];
	double b = polynom[0];

	if (a == 0.0) {
		throw std::runtime_error("Cannot devide by zero");
	}
	return (void) (std::cout << "In ℝ, the solution is: x = " << (-b / a) << std::endl);
}

void Solver::Solve2(Polynom& polynom) {
	double a = polynom[2];
	double b = polynom[1];
	double c = polynom[0];

	double delta = b * b - 4 * a * c;

	std::cout << "Discriminant: Δ = " << delta << std::endl;

	if (delta == 0) {
		return (void) (std::cout << "Discriminant is strictly 0, in ℝ the solution is:" << std::endl
								 << "x = " << (- b / 2.0 / a) << std::endl);
	}

	if (delta < 0.0) {
		double left = -b / 2.0 / a;
		double right = sqrtf(-delta) / 2.0 / a;

		std::cout << "Discriminant is strictly negative, in ℂ the two solutions are:" << std::endl
				  << "x1 = " << left << (right < 0 ? " + " : " - " ) << (right < 0 ? -right : right) << " i" << std::endl
				  << "x2 = " << left << (right < 0 ? " - " : " + " ) << (right < 0 ? -right : right) << " i" << std::endl;
	}

	if (delta > 0.0) {
		std::cout << "Discriminant is strictly positive, in ℝ the two solutions are:" << std::endl
				  << "x1 = " <<  ((-b - sqrtf(delta)) / 2.0 / a) << std::endl
				  << "x2 = " << ((-b + sqrtf(delta)) / 2.0 / a) << std::endl;
	}
}
