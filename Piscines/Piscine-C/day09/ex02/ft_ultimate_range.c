/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 08:59:22 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/15 13:54:48 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_ultimate_range(int **range, int min, int max)
{
	int		i;
	int		*tab;

	if (min >= max)
	{
		tab = NULL;
		return (0);
	}
	tab = malloc(sizeof(int) * (max - min));
	if (!tab)
		return (-1);
	i = 0;
	while (min < max)
		tab[i++] = min++;
	*range = tab;
	return (i);
}
