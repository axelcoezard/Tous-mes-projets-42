/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 19:23:56 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/15 13:54:23 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int		i;
	int		*tab;

	if (min >= max)
		return (NULL);
	i = 0;
	tab = malloc((max - min) * sizeof(int));
	if (!tab)
		return (NULL);
	while (min < max)
		tab[i++] = min++;
	return (tab);
}
