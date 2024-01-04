/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:07:52 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/19 14:14:35 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_display_char(va_list params, t_flags flags)
{
	char	c;

	(void) flags;
	c = (char) va_arg(params, int);
	ft_putchar_fd(c, 1);
	return (1);
}
