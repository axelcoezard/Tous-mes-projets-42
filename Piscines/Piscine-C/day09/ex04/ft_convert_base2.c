/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 14:33:35 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/26 01:38:23 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_check_base(char	*base);

int	ft_find_base(char c, char *base)
{
	int		count;

	count = 0;
	while (base[count] != '\0')
	{
		if (c == base[count])
			return (count);
		count++;
	}
	return (-1);
}

int	ft_is_in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] && base[i] != c)
		i++;
	return (base[i] != '\0');
}

int	ft_atoi_base(char *str, char *base)
{
	int		sign;
	int		res;
	int		base_size;

	base_size = ft_check_base(base);
	if (!base_size)
		return (0);
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	while (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign *= -1;
	res = 0;
	while (ft_is_in_base(*str, base))
	{
		res *= base_size;
		res += ft_find_base(*str, base);
		str++;
	}
	return (sign * res);
}
