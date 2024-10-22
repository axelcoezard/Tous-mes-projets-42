/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:32:44 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/05 15:15:35 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_fdf	*ft_window_open(int width, int height)
{
	t_fdf	*fdf;
	int		n;

	fdf = (t_fdf *) malloc(sizeof(t_fdf));
	if (fdf == NULL)
		return (NULL);
	fdf->width = width;
	fdf->height = height;
	fdf->mlx = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx, width, height, "FdF");
	fdf->image = mlx_new_image(fdf->mlx, width, height);
	fdf->buffer = (int *) mlx_get_data_addr(fdf->image, &n, &n, &n);
	n = 0;
	while (n < 256)
		fdf->keyboard[n++] = 0;
	mlx_hook(fdf->window, 2, 1L << 0, ft_key_press_hook, fdf);
	mlx_hook(fdf->window, 3, 1L << 1, ft_key_release_hook, fdf);
	mlx_hook(fdf->window, 4, 1L << 2, ft_mouse_press_hook, fdf);
	mlx_hook(fdf->window, 5, 1L << 3, ft_mouse_release_hook, fdf);
	mlx_hook(fdf->window, 6, 1L << 6, ft_mouse_move_hook, fdf);
	mlx_hook(fdf->window, 17, 0L, ft_quit_hook, fdf);
	return (fdf);
}

void	ft_window_loop(t_fdf *fdf, int (*hook)())
{
	if (fdf != NULL)
	{
		mlx_loop_hook(fdf->mlx, hook, fdf);
		mlx_loop(fdf->mlx);
	}
}

void	ft_window_update(t_fdf *fdf)
{
	if (fdf != NULL)
	{
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image, 0, 0);
	}
}

void	ft_window_clear(t_fdf *fdf, int color)
{
	int		x;

	x = fdf->width * fdf->height - 1;
	while (x >= 0)
	{
		fdf->buffer[x] = color;
		x--;
	}
}

void	ft_window_close(t_fdf *fdf)
{
	int		x;

	if (fdf != NULL)
	{
		x = fdf->map->width * fdf->map->height - 1;
		mlx_destroy_window(fdf->mlx, fdf->window);
		while (x >= 0)
			free(fdf->map->points[x--]);
		free(fdf->map->points);
		free(fdf->map);
		free(fdf->camera);
		free(fdf);
		exit(EXIT_SUCCESS);
	}
}
