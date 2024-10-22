/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:09:12 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/20 11:12:15 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv1.h"

int main(int argc, char** argv) {
	// Check if valid or throw usage
	if (argc < 2 || argc > 3) {
		std::cout << "Usage: " << argv[0] << " <polynomial equation> <--no-strict>" << std::endl;
		return 1;
	}

	// Check if should not be strict in flags
	bool strict = true;
	if (argc == 3 && (std::strcmp(argv[2], "--no-strict") == 0)) {
		strict = false;
	}

	// Parse and solve
	Polynom polynom;
	try {
		Parser::Parse(argv[1], polynom, strict);
		Solver::Solve(polynom);
	} catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
