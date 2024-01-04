/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:09:12 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/18 09:28:29 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_fd_recursive(long nbr, int fd)
{
	if (nbr > 0)
	{
		ft_putnbr_fd_recursive(nbr / 10, fd);
		ft_putchar_fd(nbr % 10 + '0', fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr *= -1;
	}
	if (nbr == 0)
		ft_putchar_fd(nbr + '0', fd);
	else
		ft_putnbr_fd_recursive(nbr, fd);
}
