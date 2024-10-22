/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:42:57 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/26 21:10:18 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_rush.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		ft_putchar(*str), str++;
}

int	ft_print_error(int code)
{
	if (code == FT_ERROR)
		ft_putstr("Error\n");
	if (code == FT_DICT_ERROR)
		ft_putstr("Dict Error\n");
	return (0);
}
