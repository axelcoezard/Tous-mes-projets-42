/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:35:31 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/27 15:01:46 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

struct s_flags
{
	char	type;
};
typedef struct s_flags	t_flags;

int		ft_printf_char(va_list params, t_flags flags);
int		ft_printf_string(va_list params, t_flags flags);
int		ft_printf_ptr(va_list params, t_flags flags);
int		ft_printf_decimal(va_list params, t_flags flags);
int		ft_printf_integer(va_list params, t_flags flags);
int		ft_printf_udecimal(va_list params, t_flags flags);
int		ft_printf_hex(va_list params, t_flags flags);
int		ft_printf_percent(va_list params, t_flags flags);

int		ft_printf(const char *format, ...);

#endif
