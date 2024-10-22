/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 14:07:17 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/24 09:07:37 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_tail.h"

int	ft_atoi(char *nbr)
{
	int		sign;
	int		res;

	sign = 1;
	while (*nbr == ' ' || *nbr == '\t' || *nbr == '\n'
		|| *nbr == '\v' || *nbr == '\f' || *nbr == '\r')
		nbr++;
	while (*nbr == '+' || *nbr == '-')
		if (*nbr++ == '-')
			sign *= -1;
	res = 0;
	while (*nbr >= '0' && *nbr <= '9')
	{
		res *= 10;
		res += *nbr - '0';
		nbr++;
	}		
	return (sign * res);
}
