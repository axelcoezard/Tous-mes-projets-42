/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 17:01:18 by achansel          #+#    #+#             */
/*   Updated: 2021/09/26 19:52:15 by achansel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_rush.h"

char	*ft_strndup(char *str, int n)
{
	char	*ret;
	int		i;

	ret = malloc(n + 1);
	i = 0;
	while (i < n)
		ret[i] = str[i], i++;
	ret[i] = '\0';
	return (ret);
}

int	is_delimiter(char *str, char *delim)
{
	int	occ;
	int	i;

	occ = 0;
	i = ft_strlen(delim);
	while (*delim)
		if (*str++ == *delim++)
			occ++;
	return (occ == i);
}

char	**push_into_charpp_array(char **arr, int arr_sz, char *newstr)
{
	char	**newarr;
	int		i;

	newarr = malloc((arr_sz + 2) * sizeof(char *));
	i = 0;
	while (i < arr_sz)
		newarr[i] = arr[i], i++;
	newarr[i++] = newstr;
	newarr[i] = 0;
	if (arr)
		free(arr);
	return (newarr);
}

int	set_word_and_reset_counter(char **cw, char *str)
{
	*cw = str;
	return (0);
}

char	**ft_split(char *str, char *delim)
{
	char	**words;
	int		wsz;
	char	*cw;
	int		cwl;

	wsz = 0;
	cwl = 0;
	cw = 0;
	words = push_into_charpp_array(0, wsz, 0);
	while (*str)
	{
		if (!is_delimiter(str, delim) && !cw)
			cwl = set_word_and_reset_counter(&cw, str);
		if (is_delimiter(str, delim) && cw)
		{
			words = push_into_charpp_array(words, wsz++, ft_strndup(cw, cwl));
			cw = 0;
			str += ft_strlen(delim) - 1;
		}
		cwl++;
		str++;
	}
	if (cw)
		words = push_into_charpp_array(words, wsz++, ft_strndup(cw, cwl));
	return (words);
}
