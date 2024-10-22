/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 14:07:17 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/28 07:53:47 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft.h"

int	ft_atoi(char *nbr)
{
	int		sign;
	int		res;
	int		i;

	sign = 1;
	i = 0;
	while (*nbr == ' ' || *nbr == '\t' || *nbr == '\n'
		|| *nbr == '\v' || *nbr == '\f' || *nbr == '\r')
		nbr++;
	while (*nbr == '+' || *nbr == '-')
		if (*nbr++ == '-')
			sign *= -1;
	res = 0;
	while (nbr[i] >= '0' && nbr[i] <= '9' && i < ft_strlen(nbr) - 3)
	{
		res *= 10;
		res += nbr[i] - '0';
		i++;
	}
	return (sign * res);
}
