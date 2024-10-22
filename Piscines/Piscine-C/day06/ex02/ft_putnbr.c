/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 10:48:37 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/12 13:24:22 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

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
