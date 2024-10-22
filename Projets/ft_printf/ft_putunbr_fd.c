/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:09:12 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/19 16:39:55 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putunbr_fd_recursive(unsigned int nbr, int fd)
{
	if (nbr > 0)
	{
		ft_putunbr_fd_recursive(nbr / 10, fd);
		ft_putchar_fd(nbr % 10 + '0', fd);
	}
}

void	ft_putunbr_fd(unsigned int nbr, int fd)
{
	if (nbr == 0)
		ft_putchar_fd(nbr + '0', fd);
	else
		ft_putunbr_fd_recursive(nbr, fd);
}
