/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tile.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:00:26 by acoezard          #+#    #+#             */
/*   Updated: 2024/02/06 12:15:04 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <ResourceType.hpp>
#include <cstdint>

struct Tile
{
	int32_t x;
	int32_t y;

	int16_t type;
	int32_t quantity;
	bool dirty = false;
};
