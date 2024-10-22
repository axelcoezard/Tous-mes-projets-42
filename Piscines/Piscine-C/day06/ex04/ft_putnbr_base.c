/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 16:07:47 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/23 13:06:59 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

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

void	ft_putnbr_recursive(long nbr, char *base, int base_size)
{
	if (nbr < 0)
		write(1, "-", 1), nbr *= -1;
	if (nbr > 0)
	{
		ft_putnbr_recursive(nbr / base_size, base, base_size);
		write(1, &base[nbr % base_size], 1);
	}
}

void	ft_putnbr_base(int nbr, char *base)
{
	int		base_size;

	base_size = ft_check_base(base);
	if (base_size)
	{
		if (nbr == 0)
			write(1, &base[0], 1);
		else
			ft_putnbr_recursive(nbr, base, base_size);
	}
}
