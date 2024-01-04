/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controllers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:13:12 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/08 12:55:20 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_key_press_hook(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESCAPE)
		ft_window_close(fdf);
	return (EXIT_SUCCESS);
}
