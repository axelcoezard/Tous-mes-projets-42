/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_udecimal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:00:13 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/27 16:41:24 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_printf_udecimal(va_list params, t_flags flags)
{
	size_t			size;
	unsigned int	udecimal;

	(void) flags;
	size = 0;
	udecimal = (unsigned int) va_arg(params, unsigned int);
	ft_putunbr_fd(udecimal, 1);
	if (udecimal == 0)
		return (1);
	while (udecimal != 0)
	{
		udecimal /= 10;
		size++;
	}
	return (size);
}
