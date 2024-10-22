/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 11:26:54 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/16 14:04:28 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_stock_str.h"

void	ft_show_tab(struct s_stock_str *par);

int	ft_strlen(char *str)
{
	int		count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

char	*ft_strcpy(char *dest, char *src)
{
	int		i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char *src)
{
	int		len;
	char	*dest;

	len = ft_strlen(src);
	dest = malloc(len + 1);
	return (ft_strcpy(dest, src));
}

struct s_stock_str	*ft_strs_to_tab(int ac, char **av)
{
	int					i;
	struct s_stock_str	*strs;

	strs = malloc(sizeof(struct s_stock_str) * (ac + 1));
	if (!strs)
		return (NULL);
	i = 0;
	while (i < ac && av[i] != 0)
	{
		strs[i].size = ft_strlen(av[i]);
		strs[i].str = av[i];
		strs[i].copy = ft_strdup(av[i]);
		i++;
	}
	strs[i].size = 0;
	strs[i].str = 0;
	strs[i].copy = 0;
	return (strs);
}
