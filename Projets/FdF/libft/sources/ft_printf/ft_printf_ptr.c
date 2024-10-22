/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:09:10 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/27 16:41:12 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_printf_ptr(va_list params, t_flags flags)
{
	unsigned long	address;
	void			*ptr;
	int				size;

	(void) flags;
	ptr = (void *) va_arg(params, void *);
	address = (unsigned long) ptr;
	ft_putstr_fd("0x", 1);
	ft_putunbr_base_fd(address, "0123456789abcdef", 1);
	size = 0;
	if (address == 0)
		return (3);
	while (address != 0)
	{
		address /= 16;
		size++;
	}
	return (size + 2);
}
