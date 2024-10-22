/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_udecimal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelcoezard <axelcoezard@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:00:13 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/11 22:39:44 by axelcoezard      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_printf_udecimal(va_list params, char flag)
{
	size_t			size;
	unsigned int	udecimal;

	(void) flag;
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
