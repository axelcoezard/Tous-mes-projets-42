/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_projection_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 09:37:20 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/08 10:58:46 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_vector3	*ft_rotate_x(t_vector3 *vector, float alpha)
{
	int		y;

	y = vector->y;
	vector->y = y * cos(alpha) + vector->z * sin(alpha);
	vector->z = -y * sin(alpha) + vector->z * cos(alpha);
	return (vector);
}

t_vector3	*ft_rotate_y(t_vector3 *vector, float beta)
{
	int		x;

	x = vector->x;
	vector->x = x * cos(beta) + vector->z * sin(beta);
	vector->z = -x * sin(beta) + vector->z * cos(beta);
	return (vector);
}

t_vector3	*ft_rotate_z(t_vector3 *vector, float gamma)
{
	int		x;
	int		y;

	x = vector->x;
	y = vector->y;
	vector->x = x * cos(gamma) - y * sin(gamma);
	vector->y = x * sin(gamma) + y * cos(gamma);
	return (vector);
}

t_vector2	*ft_projection(t_vector3 *vector, t_fdf *fdf)
{
	t_camera	*camera;
	t_vector3	*save;
	t_map		*map;
	int			x;
	int			y;

	camera = fdf->camera;
	map = fdf->map;
	x = (vector->x - map->width / 2) * camera->zoom;
	y = (vector->y - map->height / 2) * camera->zoom;
	save = ft_vector3_init(x, y, vector->z * camera->zoom);
	save = ft_rotate_x(save, camera->alpha);
	save = ft_rotate_y(save, camera->beta);
	save = ft_rotate_z(save, camera->gamma);
	x = camera->x + (save->x - save->y) * cos(0.523599);
	y = camera->y + (save->x + save->y) * sin(0.523599) - save->z;
	free(save);
	return (ft_vector2_init(x, y));
}
