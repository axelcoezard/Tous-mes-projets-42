/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 09:03:24 by lmataris          #+#    #+#             */
/*   Updated: 2021/09/30 09:05:08 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft.h"

int	ft_fill_square(t_map *tab, int x, int y, int size)
{
	int	i;
	int	j;

	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			ft_map_set(tab, x + i, y + j, tab->c_full);
			i++;
		}
		j++;
	}
	return (1);
}

int	ft_check_square(t_map *tab, int x, int y, int size)
{
	int	i;
	int	j;

	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			if (ft_map_get(tab, x + i, y + j) == tab->c_block)
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

int	ft_solve(t_map *tab, int x, int y, int size)
{
	if (x == tab->width - size + 1 && y == tab->height - size + 1)
		return (0);
	else if (y == tab->height - size + 1)
		return (ft_solve(tab, x + 1, 0, size));
	else if (ft_check_square(tab, x, y, size))
	{
		if (ft_solve(tab, x, y, size + 1))
			return (1);
		else
			return (ft_fill_square(tab, x, y, size));
	}
	else
		return (ft_solve(tab, x, y + 1, size));
}
