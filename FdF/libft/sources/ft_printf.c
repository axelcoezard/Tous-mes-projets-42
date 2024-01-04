/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:54:39 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/27 16:37:40 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_printf_check(const char flag)
{
	return (ft_strchr("cspdiuxX%", flag) != 0);
}

static int	ft_printf_switch(va_list params, t_flags flags)
{
	int	(*ft_printf[128])(va_list, t_flags);

	ft_printf['c'] = &ft_printf_char;
	ft_printf['s'] = &ft_printf_string;
	ft_printf['p'] = &ft_printf_ptr;
	ft_printf['d'] = &ft_printf_decimal;
	ft_printf['i'] = &ft_printf_integer;
	ft_printf['u'] = &ft_printf_udecimal;
	ft_printf['x'] = &ft_printf_hex;
	ft_printf['X'] = &ft_printf_hex;
	ft_printf['%'] = &ft_printf_percent;
	return (ft_printf[(int) flags.type](params, flags));
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
