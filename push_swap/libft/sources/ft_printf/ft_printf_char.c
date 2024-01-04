/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelcoezard <axelcoezard@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:07:52 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/11 22:37:31 by axelcoezard      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_printf_char(va_list params, char flag)
{
	char	c;

	(void) flag;
	c = (char) va_arg(params, int);
	ft_putchar_fd(c, 1);
	return (1);
}
