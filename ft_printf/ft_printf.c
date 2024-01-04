/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:54:39 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/21 11:53:22 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printf_check(const char flag)
{
	return (ft_strchr("cspdiuxX%", flag) != 0);
}

static int	ft_printf_switch(va_list params, t_flags flags)
{
	int	(*ft_display[128])(va_list, t_flags);

	ft_display['c'] = &ft_display_char;
	ft_display['s'] = &ft_display_string;
	ft_display['p'] = &ft_display_ptr;
	ft_display['d'] = &ft_display_decimal;
	ft_display['i'] = &ft_display_integer;
	ft_display['u'] = &ft_display_udecimal;
	ft_display['x'] = &ft_display_hex;
	ft_display['X'] = &ft_display_hex;
	ft_display['%'] = &ft_display_percent;
	return (ft_display[(int) flags.type](params, flags));
}

int	ft_printf(const char *format, ...)
{
	va_list	params;
	t_flags	flags;
	int		size;

	size = 0;
	va_start(params, format);
	while (*format)
	{
		if (*format == '%' && ft_printf_check(*(format + 1)))
		{
			flags.type = *(++format);
			size += ft_printf_switch(params, flags);
		}
		else
		{
			ft_putchar_fd(*format, 1);
			size++;
		}
		format++;
	}
	va_end(params);
	return (size);
}
