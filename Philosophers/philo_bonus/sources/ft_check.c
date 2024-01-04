/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:28:12 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/29 15:03:34 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_args(int ac, char **av)
{
	int		i;

	if (ac < 1 + MIN_ARGS)
		return (print_err("parser", "too few arguments.", 0));
	if (ac > 1 + MAX_ARGS)
		return (print_err("parser", "too much arguments.", 0));
	i = 0;
	while (++i < ac)
	{
		if (!check_int(av[i]))
			return (print_err("parser", "argument should be numeric.", 0));
		if (!check_negative(av[i]))
			return (print_err("parser", "argument should be positive.", 0));
	}
	return (1);
}

int	check_int(const char *nptr)
{
	int		nbr;
	size_t	digits;
	size_t	i;

	i = 0;
	nbr = 0;
	digits = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		digits++;
		if ((nbr * 10 + (nptr[i] - '0')) / 10 != nbr)
			return (0);
		nbr = nbr * 10 + (nptr[i] - '0');
		i++;
	}
	return (!nptr[i] && digits);
}

int	check_negative(const char *nptr)
{
	size_t	i;

	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
		return (0);
	return (1);
}
