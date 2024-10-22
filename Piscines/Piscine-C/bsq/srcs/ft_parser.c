/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 09:12:40 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/30 09:31:50 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft.h"

t_map	*ft_parser_file(t_file	*file)
{
	t_map	*map;
	int		x;
	int		y;
	char	*chars;

	map = NULL;
	x = ft_parser_validate_lines(file);
	if (x == 0)
		ft_error(FT_MAP_ERROR);
	if (x != 0)
	{
		y = ft_atoi(file->lines[0]);
		chars = ft_parser_get_types(file);
		map = ft_map_create(x, y);
		ft_map_define(map, FT_MAP_EMPTY, chars[0]);
		ft_map_define(map, FT_MAP_BLOCK, chars[1]);
		ft_map_define(map, FT_MAP_FULL, chars[2]);
		ft_map_fill(map, file);
	}
	return (map);
}

t_map	*ft_parser(char *path)
{
	t_file	*file;
	t_map	*map;

	map = NULL;
	file = ft_file_open(path, O_RDONLY);
	if (file)
	{
		if (ft_file_read(file))
			map = ft_parser_file(file);
	}
	ft_file_close(file);
	return (map);
}

char	*ft_parser_get_types(t_file *file)
{
	char	*first_line;

	first_line = file->lines[0];
	while (*first_line == ' ' || *first_line == '\t'
		|| *first_line == '\v' || *first_line == '\n')
		first_line++;
	return (first_line + ft_strlen(first_line) - 3);
}

int	ft_parser_validate_first_line(t_file *file)
{
	int		size;
	char	*first_line;
	int		len;

	size = 0;
	while (file->lines[size] != 0)
		size++;
	if (size < 2)
		return (0);
	first_line = file->lines[0];
	while (*first_line == ' ' || *first_line == '\n')
		first_line++;
	len = ft_strlen(first_line);
	if (!(*first_line >= '0' && *first_line <= '9') && len < 4)
		return (0);
	if (first_line[len - 3] == first_line[len - 2]
		|| first_line[len - 2] == first_line[len - 1]
		|| first_line[len - 3] == first_line[len - 1])
		return (0);
	return (1);
}

int	ft_parser_validate_lines(t_file *file)
{
	int		i;
	int		j;
	char	*types;
	int		size;

	if (!ft_parser_validate_first_line(file))
		return (0);
	types = ft_parser_get_types(file);
	i = 1;
	size = ft_strlen(file->lines[i]);
	while (file->lines[i] != NULL)
	{
		if (ft_strlen(file->lines[i]) != size)
			return (0);
		j = 0;
		while (file->lines[i][j] != '\0')
		{
			if (file->lines[i][j] != types[0] && file->lines[i][j] != types[1]
				&& file->lines[i][j] != types[2])
				return (0);
			j++;
		}
		i++;
	}
	return (size);
}
