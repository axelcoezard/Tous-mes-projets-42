/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 09:18:22 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/17 09:11:34 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

char	*ft_strcat(char *dest, char *src)
{
	int		i;
	int		j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

int	ac_strjoin_size(int size, char **strs, char *sep)
{
	int		i;
	int		ef_size;

	ef_size = 0;
	i = 0;
	while (i < size)
	{
		ef_size += ft_strlen(strs[i]);
		i++;
	}
	return (ef_size + ft_strlen(sep) * (size - 1));
}

char	*ft_strjoin(int size, char	**strs, char *sep)
{
	int		ef_size;
	char	*str;
	int		i;

	if (size <= 0)
		return (malloc(0));
	ef_size = ac_strjoin_size(size, strs, sep);
	str = malloc(ef_size + 1);
	if (!str)
		return (NULL);
	*str = 0;
	i = 0;
	while (i < size)
	{
		ft_strcat(str, strs[i]);
		if (i < size - 1)
			ft_strcat(str, sep);
		i++;
	}
	return (str);
}
