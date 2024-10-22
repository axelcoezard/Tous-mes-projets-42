/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:32:54 by achansel          #+#    #+#             */
/*   Updated: 2021/09/26 22:23:22 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_rush.h"

int	get_count(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
		i++;
	return (i);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[++i])
		;
	return (i);
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

int	ft_free(char **to_free)
{
	while (*to_free)
		free(*to_free++);
	return (0);
}
