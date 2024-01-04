/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 21:47:20 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/14 19:52:48 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	check_duplicates(t_tab *tab)
{
	int		i;
	int		j;

	i = 0;
	while (i < tab->size)
	{
		j = i + 1;
		while (j < tab->size)
		{
			if (tab->v[i] == tab->v[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_sorted(t_tab *tab)
{
	int	i;

	i = 0;
	while (i + 1 < tab->size)
	{
		if (tab->v[i] > tab->v[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	check_int(const char *nptr)
{
	int				nbr;
	size_t			digits;
	size_t			i;

	i = 0;
	nbr = 0;
	digits = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		digits++;
		if ((nbr * 10 + (nptr[i] - '0')) / 10 != nbr)
			return (0);
		nbr = nbr * 10 + (nptr[i] - '0');
		i++;
	}
	return (!nptr[i] && digits);
}
