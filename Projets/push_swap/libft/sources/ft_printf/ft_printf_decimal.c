/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_decimal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelcoezard <axelcoezard@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:53:56 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/11 22:37:44 by axelcoezard      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_printf_decimal(va_list params, char flag)
{
	size_t	size;
	int		decimal;

	(void) flag;
	size = 0;
	decimal = (int) va_arg(params, int);
	ft_putnbr_fd(decimal, 1);
	if (decimal == 0)
		return (1);
	if (decimal < 0)
		size++;
	while (decimal != 0)
	{
		decimal /= 10;
		size++;
	}
	return (size);
}
