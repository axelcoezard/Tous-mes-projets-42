/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:32:08 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/05 15:50:29 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static char	*ft_parser_get_line(int filedesc)
{
	char	*buffer;
	char	*line;

	line = ft_get_next_line(filedesc);
	if (line == NULL)
		return (NULL);
	buffer = ft_strtrim(line, " \n");
	free(line);
	return (buffer);
}

static t_fdf	*ft_parser_get_dimension(char *filename, t_fdf *fdf)
{
	int			filedesc;
	char		*line;
	char		**line_values;

	filedesc = open(filename, O_RDONLY);
	if (filedesc > 0)
	{
		line = ft_parser_get_line(filedesc);
		line_values = ft_split(line, ' ');
		while (line_values[fdf->map->width] != NULL)
		{
			free(line_values[fdf->map->width]);
			fdf->map->width++;
		}
		free(line_values);
		while (line != NULL)
		{
			fdf->map->height++;
			free(line);
			line = ft_parser_get_line(filedesc);
		}
		free(line);
		close(filedesc);
	}
	return (fdf);
}

static t_fdf	*ft_parser_file(t_fdf *fdf, int filedesc)
{
	char	*line;
	char	**points;
	int		y;
	int		x;

	line = ft_parser_get_line(filedesc);
	y = 0;
	while (line != NULL)
	{
		points = ft_split(line, ' ');
		free(line);
		x = -1;
		while (points[++x] != NULL)
		{
			ft_map_set_point(fdf->map, x, y, ft_atoi(points[x]));
			free(points[x]);
		}
		free(points);
		line = ft_parser_get_line(filedesc);
		y++;
	}
	free(line);
	return (fdf);
}

int	ft_parser(t_fdf *fdf, char *filename)
{
	int		filedesc;

	fdf = ft_map_init(fdf, 0, 0);
	fdf = ft_parser_get_dimension(filename, fdf);
	fdf->map = ft_map_init_points(fdf->map);
	filedesc = open(filename, O_RDONLY);
	if (filedesc > 0)
	{
		fdf = ft_parser_file(fdf, filedesc);
		close(filedesc);
		return (1);
	}
	return (0);
}
