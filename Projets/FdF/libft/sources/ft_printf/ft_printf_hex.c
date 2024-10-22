/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:07:54 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/27 16:40:51 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_printf_hex(va_list params, t_flags flags)
{
	unsigned int	d;
	int				size;

	(void) flags;
	d = (unsigned int) va_arg(params, unsigned int);
	if (ft_isupper(flags.type))
		ft_putunbr_base_fd(d, "0123456789ABCDEF", 1);
	if (ft_islower(flags.type))
		ft_putunbr_base_fd(d, "0123456789abcdef", 1);
	size = 0;
	if (d == 0)
		return (1);
	while (d != 0)
	{
		d /= 16;
		size++;
	}
	return (size);
}
