/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 09:34:33 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/28 09:27:51 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft.h"

void	ft_map_define(t_map *map, int id, char c)
{
	if (id == FT_MAP_EMPTY)
		map->c_empty = c;
	else if (id == FT_MAP_FULL)
		map->c_full = c;
	else if (id == FT_MAP_BLOCK)
		map->c_block = c;
}
