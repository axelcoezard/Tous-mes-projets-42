/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 13:48:47 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/08 15:35:21 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ac_print_number(int x)
{
	char	xa;
	char	xb;

	xa = x / 10 + '0';
	xb = x % 10 + '0';
	write(1, &xa, 1);
	write(1, &xb, 1);
}

void	ft_print_comb2(void)
{
	int		x;
	int		y;

	x = 0;
	while (x <= 98)
	{
		y = x + 1;
		while (y <= 99)
		{
			ac_print_number(x);
			write(1, " ", 1);
			ac_print_number(y);
			if (x != 98 || y != 99)
				write(1, ", ", 2);
			y++;
		}
		x++;
	}
}
