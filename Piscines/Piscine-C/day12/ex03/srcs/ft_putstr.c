/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:54:33 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/28 11:03:39 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_hexdump.h"

int	ft_putstr(char *str)
{
	while (*str)
		ft_putchar(*str), str++;
	return (1);
}

int	ft_strlen(char *str)
{
	int		count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

char	*ft_strcpy(char *dest, char *src, int len)
{
	int		i;

	i = 0;
	while (i < len && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char *src, int len)
{
	char	*dest;

	dest = malloc(len + 1);
	return (ft_strcpy(dest, src, len));
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2 && s1++ && s2++)
		;
	return (*s1 - *s2);
}
