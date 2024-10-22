/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:07:52 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/23 17:34:38 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_printf_char(va_list params, t_flags flags)
{
	char	c;

	(void) flags;
	c = (char) va_arg(params, int);
	ft_putchar_fd(c, 1);
	return (1);
}
