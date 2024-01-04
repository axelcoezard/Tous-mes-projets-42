/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:35:31 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/21 11:53:31 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

struct s_flags
{
	char	type;
};
typedef struct s_flags	t_flags;

int		ft_printf(const char *format, ...);

void	ft_putunbr_fd(unsigned int nbr, int fd);
void	ft_putunbr_base_fd(unsigned long nbr, char *base, int fd);

t_flags	ft_flags_init(void);

int		ft_display_char(va_list params, t_flags flags);
int		ft_display_string(va_list params, t_flags flags);
int		ft_display_ptr(va_list params, t_flags flags);
int		ft_display_decimal(va_list params, t_flags flags);
int		ft_display_integer(va_list params, t_flags flags);
int		ft_display_udecimal(va_list params, t_flags flags);
int		ft_display_hex(va_list params, t_flags flags);
int		ft_display_percent(va_list params, t_flags flags);

#endif
