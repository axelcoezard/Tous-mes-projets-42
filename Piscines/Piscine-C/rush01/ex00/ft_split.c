/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 14:07:07 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/19 23:41:07 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

int	ft_split_size(char *str)
{
	int		i;
	int 	size;

	i = 0;
	size = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
			size++;
		i++;	
	}
	return (size);
}

int	ft_split_copy(int *dest, char *from, int start, int end)
{
	char	*word;
	int		i;
	
	word = malloc(end - start + 1);
	if (!word)
		return (ft_print_error());
	i = 0;
	while (from[i + start] != ' ' && from[i + start] != '\0')
		word[i] = from[i + start], i++;
	word[i] = '\0';
	*dest = ft_atoi(word);
	return (*dest);
}

int	*ft_split(char *str)
{
	int		*numbers;
	int		size;
	int		i;
	int		j;
	int 	k;

	size = ft_split_size(str);
	numbers = malloc(size * sizeof(int) + 1);
	numbers[size] = -1;
	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\0')
			i++;
		else
		{
			j = 0;
			while (str[i + j] != ' ' && str[i + j] != '\0')
			   j++;
			ft_split_copy(&numbers[k], str, i, i + j + 1);
			i += j;
			k++;
		}
	}
	return (numbers);
}
