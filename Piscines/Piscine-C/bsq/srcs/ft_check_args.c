/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 09:12:35 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/28 14:04:08 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft.h"

int	ft_check_args(int ac, char **av)
{
	(void) av;
	if (ac == 1)
		return (FT_SOLVE_INPUT);
	return (FT_SOLVE_FILE);
}
