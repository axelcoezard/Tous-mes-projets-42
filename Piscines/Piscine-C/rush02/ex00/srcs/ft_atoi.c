/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 14:07:17 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/26 21:36:00 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_rush.h"

int	ft_is_numeric(char *str)
{
	while (*str == ' ' || *str == '\n'
		|| *str == '\t' || *str == '-' || *str == '+')
		str++;
	if (*str < '0' || *str > '9')
		return (0);
	return (1);
}

t_bignum	ft_atoi(char *nbr)
{
	int			neg;
	t_bignum	res;

	neg = 0;
	while (*nbr == ' ' || *nbr == '\t' || *nbr == '\n'
		|| *nbr == '\v' || *nbr == '\f' || *nbr == '\r')
		nbr++;
	while (*nbr == '+' || *nbr == '-')
		if (*nbr++ == '-')
			neg = !neg;
	res = 0;
	while (*nbr >= '0' && *nbr <= '9')
	{
		res *= 10;
		res += *nbr - '0';
		nbr++;
	}
	if (neg)
		res = -res;
	return (res);
}
