/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 08:48:45 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/30 16:27:14 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_puthex(char c)
{
	char	a;
	char	b;
	char	*base;

	base = "0123456789abcdef";
	if (c < 0)
	{
		a = base[(256 + c) / 16];
		b = base[(256 + c) % 16];
	}
	else
	{
		a = base[c / 16];
		b = base[c % 16];
	}
	write(1, "\\", 1);
	write(1, &a, 1);
	write(1, &b, 1);
}

void	ft_putstr_non_printable(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] > 31 && str[i] < 127)
			write(1, &str[i], 1);
		else
			ft_puthex(str[i]);
		i++;
	}
}
