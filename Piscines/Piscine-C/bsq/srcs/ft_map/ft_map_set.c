/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 09:34:33 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/30 09:43:15 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft.h"

int	ft_map_set(t_map *map, int x, int y, char c)
{
	if (x < 0 || x >= map->width)
		return (0);
	if (y < 0 || y >= map->height)
		return (0);
	map->grid[x + y * map->width] = c;
	return (1);
}
