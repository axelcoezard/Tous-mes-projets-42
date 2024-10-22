/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dict.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:12:14 by achansel          #+#    #+#             */
/*   Updated: 2021/09/26 23:05:07 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_rush.h"

int	is_line_valid(char **line)
{
	int	parts;
	int	i;

	parts = get_count(line);
	if (parts != 2)
		return (ft_free(line));
	if (!ft_is_numeric(line[0]))
		return (ft_free(line));
	i = 0;
	while (line[1][i])
	{
		if (!(line[1][i] >= 'a' && line[1][i] <= 'z')
				&& !(line[1][i] >= 'A' && line[1][i] <= 'Z')
				&& !(line[1][i] == '-') && !(line[1][i] == ' '))
			return (ft_free(line));
		i++;
	}
	return (1);
}

void	ft_remove_duplicates(t_entry **entries)
{
	int		i;

	i = 0;
	while (entries[i])
	{
		if (entries[i]->n > 19 && entries[i]->n % 10 != 0)
		{
			entries[i]->n = -1;
			free(entries[i]->str);
			entries[i]->str = ft_strdup("zero");
		}
		i++;
	}
}

void	ft_sort_dict_entry(t_entry **entries, int size)
{
	int		cursor;
	int		i;
	t_entry	*tmp;
	int		max;

	ft_remove_duplicates(entries);
	cursor = 0;
	while (cursor < size)
	{
		i = cursor;
		max = i;
		while (i < size)
		{
			if (entries[i]->n > entries[max]->n)
				max = i;
			i++;
		}
		tmp = entries[cursor];
		entries[cursor] = entries[max];
		entries[max] = tmp;
		cursor++;
	}
}

t_entry	**split_dict_entry(char **lines)
{
	int			i;
	int			size;
	t_entry		**entries;
	char		**line;

	size = get_count(lines);
	entries = malloc((size + 1) * sizeof(t_entry *));
	i = 0;
	while (i < size)
	{
		line = ft_split(lines[i], ": ");
		if (*line)
		{
			entries[size - i - 1] = malloc(sizeof(t_entry));
			entries[size - i - 1]->n = ft_atoi(line[0]);
			entries[size - i - 1]->str = line[1];
			free(line[0]);
		}
		free(line), free(lines[i]);
		i++;
	}
	entries[i] = 0;
	ft_sort_dict_entry(entries, size), free(lines);
	return (entries);
}

int	free_dict_entries(t_entry **entries)
{
	int	i;

	i = 0;
	while (entries[i])
	{
		if (entries[i]->str)
			free(entries[i]->str);
		free(entries[i]);
		i++;
	}
	free(entries);
	return (0);
}
