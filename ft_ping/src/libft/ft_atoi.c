/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:23:35 by acoezard          #+#    #+#             */
/*   Updated: 2023/04/24 11:28:32 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static int ft_atoi_overflow(int sign)
{
	if (sign < 0)
		return (0);
	return (-1);
}

static int ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\v'
		|| c == '\n' || c == '\f' || c == '\r');
}

static int ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int ft_atoi(const char *nptr)
{
	unsigned long	nbr;
	int				sign;

	while (ft_isspace(*nptr))
		nptr++;
	sign = 1;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	nbr = 0;
	while (ft_isdigit(*nptr))
	{
		if ((nbr * 10 + (*nptr - '0')) / 10 != nbr)
			return (ft_atoi_overflow(sign));
		nbr *= 10;
		nbr += *nptr - '0';
		nptr++;
	}
	return (sign * nbr);
}
