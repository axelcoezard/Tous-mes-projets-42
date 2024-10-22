/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsq.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 09:12:24 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/29 15:31:37 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft.h"

void	ft_bsq(int ac, char **av)
{
	t_map	*map;
	int		i;	
	int		status;

	status = ft_check_args(ac, av);
	if (status == FT_SOLVE_INPUT)
		ft_read_input();
	if (status == FT_SOLVE_FILE)
	{
		i = 1;
		while (i < ac)
		{
			map = ft_parser(av[i]);
			if (map != NULL)
				ft_solve(map, 0, 0, 0), ft_map_print(map);
			ft_map_destroy(map);
			i++;
		}
	}
}
