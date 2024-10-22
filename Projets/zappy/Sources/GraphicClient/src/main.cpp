/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:37:34 by acoezard          #+#    #+#             */
/*   Updated: 2024/01/29 11:48:04 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenGL/Window.hpp"
#include "GraphicClient.hpp"

int main(int argc, char **argv)
{
	GraphicClient client;
	client.Initialize(argc, argv);
	client.Start();
	return EXIT_SUCCESS;
}
