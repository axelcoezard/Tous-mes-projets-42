/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:38:49 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/08 10:23:36 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_draw_pixel(t_fdf *fdf, int x, int y, int color)
{
	if (fdf == NULL || fdf->buffer == NULL)
		return ;
	if (x < 0 || x > fdf->width - 1)
		return ;
	if (y < 0 || y > fdf->height - 1)
		return ;
	fdf->buffer[x + y * fdf->width] = color;
}

void	ft_draw_line(t_fdf *fdf, t_vector2 *a, t_vector2 *b, int color)
{
	t_vector2	*delta;
	int			steps;
	int			i;
	float		x;
	float		y;

	delta = ft_vector2_init(b->x - a->x, b->y - a->y);
	steps = fmax(abs(delta->x), abs(delta->y));
	x = a->x;
	y = a->y;
	i = 0;
	while (i <= steps)
	{
		ft_draw_pixel(fdf, x, y, color);
		x += delta->x / (float) steps;
		y += delta->y / (float) steps;
		i++;
	}
	free(a);
	free(b);
	free(delta);
}

void	ft_draw_projection(t_fdf *fdf, int x, int y, int drawcode)
{
	t_vector2	*a;
	t_vector2	*b;
	int			color;

	color = 0x000000;
	a = ft_projection(ft_map_get_point(fdf->map, x, y), fdf);
	if (drawcode == DRAW_HORIZONTAL)
		b = ft_projection(ft_map_get_point(fdf->map, x + 1, y), fdf);
	else
	{
		b = ft_projection(ft_map_get_point(fdf->map, x, y + 1), fdf);
		color = 0x0000f0;
	}
	ft_draw_line(fdf, a, b, color);
}
