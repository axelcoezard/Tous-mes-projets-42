/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 11:43:10 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/30 09:13:45 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft.h"

int	ft_is_sep(char *charset, char c)
{
	int		i;

	if (c == '\0')
		return (1);
	i = 0;
	while (charset[i] != '\0')
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_split_size(char *str, char *seps)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (str[i] != '\0')
	{
		if (!ft_is_sep(seps, str[i]) && ft_is_sep(seps, str[i + 1]))
			size++;
		i++;
	}
	return (size);
}

char	*ft_split_copy(char *from, char *seps, int start, int end)
{
	char	*word;
	int		i;

	word = malloc(end - start + 1);
	i = 0;
	while (i + start < end && !ft_is_sep(seps, from[i + start]))
		word[i] = from[i + start], i++;
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str, char *charset)
{
	char	**words;
	int		size;
	int		i;
	int		j;
	int		k;

	size = ft_split_size(str, charset);
	words = malloc((size + 1) * sizeof(char *));
	words[size] = 0;
	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (ft_is_sep(charset, str[i]))
			i++;
		else
		{
			j = 0;
			while (!ft_is_sep(charset, str[i + j]))
				j++;
			words[k++] = ft_split_copy(str, charset, i, i + j + 1);
			i += j;
		}
	}
	return (words);
}
