/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 15:47:01 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/18 19:50:39 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

t_tab	*ft_create_tab(int size)
{
	int		i;
	t_tab	*tab;

	if (size < 1)
		return (NULL);
	tab = malloc(sizeof(t_tab));
	if (!tab)
		return (NULL);
	tab->size = size;
	tab->grid = malloc(size * size * sizeof(int));
	if (!tab->grid)
		return (NULL);
	i = 0;
	while (i < tab->size * tab->size)
		tab->grid[i] = 0, i++;
	return (tab);
}

int	ft_get_tab(t_tab *tab, int x, int y)
{
	if (x >= tab->size)
		return (0);
	if (y >= tab->size)
		return (0);
	return (tab->grid[x + y * tab->size]);
}

void	ft_set_tab(t_tab *tab, int x, int y, int height)
{
	if (height > tab->size)
		height = tab->size;
	if (height < 0)
		height = 0;
	if (x < tab->size && y < tab->size)
		tab->grid[x + y * tab->size] = height;
}

/**
 * Affiche le contenu de tab->grid dans la
 * sortie standard avec le formatage demande
 * dans le sujet.
 *
 * @param tab Le pointeur sur la structure t_tab.
 */
void	ft_print_tab(t_tab *tab)
{
	int		x;
	int		y;

	y = 0;
	while (y < tab->size)
	{
		x = 0;
		while (x < tab->size)
		{
			ft_putnbr(ft_get_tab(tab, x, y));
			if (x < tab->size - 1)
				ft_putchar(' ');
			x++;
		}
		ft_putchar('\n');
		y++;
	}
}

/**
 * Libere la memoire allouee a la structure t_tab
 * et a t_tab->grid.
 *
 * @param tab Le pointeur sur la structure t_tab.
 */
void	ft_destroy_tab(t_tab *tab)
{
	free(tab->grid);
	free(tab);
}
