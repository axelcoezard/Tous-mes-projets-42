/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_integer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:18:40 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/19 16:05:21 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_display_integer(va_list params, t_flags flags)
{
	size_t	size;
	int		i;

	(void) flags;
	size = 0;
	i = (int) va_arg(params, int);
	ft_putnbr_fd(i, 1);
	if (i == 0)
		return (1);
	if (i < 0)
		size++;
	while (i != 0)
	{
		i /= 10;
		size++;
	}
	return (size);
}
