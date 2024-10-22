/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 09:28:50 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/09 09:56:41 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_sort_int_tab(int *tab, int size)
{
	int		cursor;
	int		i;
	int		tmp;
	int		min;

	cursor = 0;
	while (cursor < size)
	{
		i = cursor;
		min = i;
		while (i < size)
		{
			if (tab[i] < tab[min])
				min = i;
			i++;
		}
		tmp = tab[cursor];
		tab[cursor] = tab[min];
		tab[min] = tmp;
		cursor++;
	}
}
