/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:47:53 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/08 11:45:38 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_camera_init(t_fdf *fdf)
{
	fdf->camera = (t_camera *) malloc(sizeof(t_camera));
	if (fdf->camera == NULL)
		return (0);
	fdf->camera->x = fdf->width / 2;
	fdf->camera->y = fdf->height / 2;
	fdf->camera->zoom = 10;
	fdf->camera->alpha = 0;
	fdf->camera->beta = 0;
	fdf->camera->gamma = 0;
	return (1);
}

void	ft_camera_controls(t_fdf *fdf)
{
	if (fdf->keyboard[KEY_LEFT] || fdf->keyboard[KEY_A])
		ft_camera_move(fdf->camera, -10, 0);
	if (fdf->keyboard[KEY_RIGHT] || fdf->keyboard[KEY_D])
		ft_camera_move(fdf->camera, 10, 0);
	if (fdf->keyboard[KEY_UP] || fdf->keyboard[KEY_W])
		ft_camera_move(fdf->camera, 0, -10);
	if (fdf->keyboard[KEY_DOWN] || fdf->keyboard[KEY_S])
		ft_camera_move(fdf->camera, 0, 10);
}

t_camera	*ft_camera_move(t_camera *camera, int x, int y)
{
	camera->x += x;
	camera->y += y;
	return (camera);
}

t_camera	*ft_camera_rotate(t_camera *camera, float a, float b, float g)
{
	camera->alpha += a;
	camera->beta += b;
	camera->gamma += g;
	return (camera);
}

t_camera	*ft_camera_zoom(t_camera *camera, int zoom)
{
	if (camera->zoom + zoom > 0)
		camera->zoom += zoom;
	return (camera);
}
