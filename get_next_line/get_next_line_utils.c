/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:19:48 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/21 10:09:31 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && *s != 0)
	{
		s++;
		len++;
	}
	return (len);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	res;

	res = 0;
	if (size > 0)
	{
		while (size > 1 && src[res])
		{
			dest[res] = src[res];
			res++;
			size--;
		}
		dest[res] = 0;
	}
	while (src[res] != 0)
	{
		res++;
	}
	return (res);
}

char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dest);
	j = 0;
	while (src[j] != 0)
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = 0;
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		dest_len;

	dest_len = ft_strlen(s);
	dest = (char *) malloc(dest_len + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s, dest_len);
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *) s;
	i = 0;
	while (str[i] != (unsigned char) c)
	{
		if (str[i] == '\0')
			return (NULL);
		i++;
	}
	return (str + i);
}
