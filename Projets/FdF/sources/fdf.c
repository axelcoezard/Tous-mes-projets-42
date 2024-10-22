/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 14:48:18 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/05 16:33:19 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int static	ft_throw_error(void)
{
	ft_printf("Error.\n");
	return (EXIT_FAILURE);
}

int static	ft_throw_usage(void)
{
	ft_printf("Usage: ./fdf [filename]\n");
	return (EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	t_fdf	*fdf;

	if (ac == 2)
	{
		(void) ac;
		fdf = ft_window_open(1280, 720);
		if (fdf == NULL)
			return (ft_throw_error());
		if (!ft_parser(fdf, av[1]))
			return (ft_throw_error());
		if (!ft_camera_init(fdf))
			return (ft_throw_error());
		ft_window_loop(fdf, ft_loop_hook);
		return (EXIT_SUCCESS);
	}
	ft_throw_error();
	return (ft_throw_usage());
}
