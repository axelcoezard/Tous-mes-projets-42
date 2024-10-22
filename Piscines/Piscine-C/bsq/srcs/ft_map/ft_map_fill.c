/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 09:34:33 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/28 17:27:32 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft.h"

int	ft_map_fill(t_map *map, t_file *file)
{
	int		x;
	int		y;

	y = 1;
	while (file->lines[y] != 0)
	{
		x = 0;
		while (file->lines[y][x] != '\0')
		{
			ft_map_set(map, x, y - 1, file->lines[y][x]);
			x++;
		}
		y++;
	}
	return (1);
}
