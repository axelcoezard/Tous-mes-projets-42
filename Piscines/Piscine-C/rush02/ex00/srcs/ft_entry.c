/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_entry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 20:18:59 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/26 22:58:17 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_rush.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2 && s1++ && s2++)
		;
	return (*s1 - *s2);
}

t_entry	*get_entry_by_n(t_entry **entries, t_ubignum n)
{
	int		i;

	i = 0;
	while (entries[i] != 0)
	{
		if (entries[i]->n == n)
			return (entries[i]);
		i++;
	}
	return (0);
}

t_entry	*get_entry_by_str(t_entry **entries, char	*str)
{
	int		i;

	i = 0;
	while (entries[i] != 0)
	{
		if (ft_strcmp(entries[i]->str, str) == 0)
			return (entries[i]);
		i++;
	}
	return (0);
}

t_entry	*get_entry_first_dividing(t_entry **entries, t_ubignum number)
{
	int		i;

	i = 0;
	while (entries[i] != 0)
	{
		if (number / entries[i]->n > 0)
			return (entries[i]);
		i++;
	}
	return (0);
}
