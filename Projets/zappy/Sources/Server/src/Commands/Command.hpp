/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:35:30 by acoezard          #+#    #+#             */
/*   Updated: 2024/02/06 15:52:05 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Game;
class Client;

struct Command
{
	virtual ~Command(void) {}

	virtual bool BeforeQueue(Game* game, Client* player, std::vector<std::string> args) = 0;
	virtual bool AfterQueue(Game* game, Client* player, std::vector<std::string> args) = 0;
};
