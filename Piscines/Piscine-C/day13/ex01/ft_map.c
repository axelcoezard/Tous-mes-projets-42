/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 14:58:29 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/21 15:20:47 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_map(int *tab, int length, int (*f)(int))
{
	int		i;
	int		*res;

	i = 0;
	res = malloc(sizeof(int) * length);
	while (i < length)
	{
		res[i] = f(tab[i]);
		i++;
	}
	return (res);
}
