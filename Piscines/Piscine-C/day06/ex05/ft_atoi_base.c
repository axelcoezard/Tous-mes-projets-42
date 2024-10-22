/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:56:54 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/23 10:27:35 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_check_base(char	*base)
{
	int		i;
	int		j;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		if (base[i] == ' ' || base[i] == '\n' || base[i] == '\t'
			|| base[i] == '\v' || base[i] == '\f' || base[i] == '\r')
			return (0);
		j = i + 1;
		while (base[j] != '\0')
			if (base[i] == base[j++])
				return (0);
		i++;
	}
	if (i <= 1)
		return (0);
	return (i);
}

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
