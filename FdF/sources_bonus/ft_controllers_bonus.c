/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controllers_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:13:12 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/08 11:44:38 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_key_press_hook(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESCAPE)
		ft_window_close(fdf);
	fdf->keyboard[keycode] = 1;
	ft_loop_hook(fdf);
	return (EXIT_SUCCESS);
}

int	ft_key_release_hook(int keycode, t_fdf *fdf)
{
	fdf->keyboard[keycode] = 0;
	return (EXIT_SUCCESS);
}

int	ft_mouse_press_hook(int button, int x, int y, t_fdf *fdf)
{
	if (button == MOUSE_SCROLL_DOWN)
		ft_camera_zoom(fdf->camera, 1);
	if (button == MOUSE_SCROLL_UP)
		ft_camera_zoom(fdf->camera, -1);
	fdf->x = x;
	fdf->y = y;
	fdf->buttons[button] = 1;
	return (EXIT_SUCCESS);
}

int	ft_mouse_release_hook(int button, int x, int y, t_fdf *fdf)
{
	(void) x;
	(void) y;
	fdf->buttons[button] = 0;
	return (EXIT_SUCCESS);
}

int	ft_mouse_move_hook(int x, int y, t_fdf *fdf)
{
	float	alpha;
	float	beta;

	fdf->prev_x = fdf->x;
	fdf->prev_y = fdf->y;
	fdf->x = x;
	fdf->y = y;
	if (fdf->buttons[MOUSE_LEFT])
	{
		alpha = (x - fdf->prev_x) * 0.002;
		beta = (y - fdf->prev_y) * 0.002;
		ft_camera_rotate(fdf->camera, beta, 0, alpha);
		ft_loop_hook(fdf);
	}
	return (EXIT_SUCCESS);
}
