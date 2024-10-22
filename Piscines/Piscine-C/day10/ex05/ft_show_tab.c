/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 11:55:15 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/19 13:05:17 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_stock_str.h"

struct s_stock_str	*ft_strs_to_tab(int ac, char **av);

void	ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ac_pow(int x, int n)
{
	int		pow;

	pow = 1;
	while (n > 1)
	{
		pow *= x;
		n--;
	}
	return (pow);
}

void	ac_putnbr_positive(int nb)
{
	int		size;
	int		n;
	char	digit;

	size = 0;
	n = nb;
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	while (size > 1)
	{
		digit = nb / ac_pow(10, size) % 10 + '0';
		write(1, &digit, 1);
		size--;
	}
	digit = nb % 10 + '0';
	write(1, &digit, 1);
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
		write(1, "-2147483648", 11);
	else
	{
		if (nb < 0)
		{
			write(1, "-", 1);
			nb *= -1;
		}
		ac_putnbr_positive(nb);
	}
}

void	ft_show_tab(struct s_stock_str *par)
{
	int		i;

	i = 0;
	while (par[i].str != 0)
	{
		ft_putstr(par[i].str);
		write(1, "\n", 1);
		ft_putnbr(par[i].size);
		write(1, "\n", 1);
		ft_putstr(par[i].copy);
		write(1, "\n", 1);
		i++;
	}
}
