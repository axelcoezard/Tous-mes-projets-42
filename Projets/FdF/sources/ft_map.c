/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:03:25 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/04 17:22:09 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_fdf	*ft_map_init(t_fdf *fdf, int width, int height)
{
	fdf->map = (t_map *) malloc(sizeof(t_map));
	fdf->map->width = width;
	fdf->map->height = height;
	return (fdf);
}

t_map	*ft_map_init_points(t_map *map)
{
	int		w;
	int		h;

	w = map->width;
	h = map->height;
	map->points = ft_calloc(h * w, sizeof(t_vector3 *));
	return (map);
}

t_map	*ft_map_set_point(t_map *map, int x, int y, int height)
{
	t_vector3	*point;

	point = ft_vector3_init(x, y, height);
	map->points[x + y * map->width] = point;
	return (map);
}

t_vector3	*ft_map_get_point(t_map *map, int x, int y)
{
	return (map->points[x + y * map->width]);
}
