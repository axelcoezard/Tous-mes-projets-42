/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 08:51:59 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/26 09:50:22 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_print_address(char *addr)
{
	char	address[16];
	long	addr_l;
	char	*base;
	int		i;

	base = "0123456789abcdef";
	addr_l = (long) addr;
	i = 0;
	while (i < 17)
	{
		if (addr_l > 0)
		{
			address[i] = base[addr_l % 16];
			addr_l /= 16;
		}
		else
			address[i] = '0';
		i++;
	}
	i = 16;
	while (i > 0)
		ft_putchar(address[i]), i--;
	ft_putchar(':');
	ft_putchar(' ');
}

void	ft_print_hex(char *buffer, int i)
{
	char	*base;
	char	c;
	char	d;
	int		j;

	base = "0123456789abcdef";
	j = 0;
	while (j < 16 && buffer[i + j])
	{
		c = buffer[i + j];
		d = buffer[i + j + 1];
		if (c != 0 || d != 0)
		{
			write(1, &base[c / 16], 1);
			write(1, &base[c % 16], 1);
			write(1, &base[d / 16], 1);
			write(1, &base[d % 16], 1);
			if (j % 2 == 0)
				write(1, " ", 1);
		}
		j += 2;
	}
	while (j < 16)
		write (1, "  ", 1), j++;
}

void	ft_print_ascii(char *buffer, int i)
{
	int		j;
	char	c;

	j = 0;
	while (j < 16 && buffer[i + j])
	{
		c = buffer[i + j];
		if (c > 31 && c < 127)
			write(1, &c, 1);
		else
			write(1, ".", 1);
		j++;
	}
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	unsigned int	i;
	char			*str;

	str = (char *) addr;
	i = 0;
	while (size > 0 && str[i])
	{
		if (i % 16 == 0)
			ft_print_address(str + i);
		ft_print_hex(str, i);
		ft_print_ascii(str, i);
		if (i % 16 == 0)
			write(1, "\n", 1);
		i += 16;
		size -= 16;
	}
	return (addr);
}
