/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 09:34:33 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/28 17:28:10 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft.h"

char	ft_map_get(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width)
		return (0);
	if (y < 0 || y >= map->height)
		return (0);
	return (map->grid[x + y * map->width]);
}
