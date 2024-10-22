/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 09:34:33 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/28 17:27:56 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft.h"

void	ft_map_print(t_map *map)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			c = ft_map_get(map, x, y);
			ft_putchar(c);
			x++;
		}
		ft_putchar('\n');
		y++;
	}
}
