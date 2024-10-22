/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:03:42 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/28 15:30:14 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_hexdump.h"

void	ft_print_address(int i, int option)
{
	char	*base;
	char	address[9];
	int		j;

	base = "0123456789abcdef";
	j = 0;
	while (j < 9 - !option)
	{
		if (i > 0)
		{
			address[j] = base[i % 16];
			i /= 16;
		}
		else
			address[j] = '0';
		j++;
	}
	j = 8 - !option;
	while (j > 0)
		ft_putchar(address[j]), j--;
	if (option == 1)
		ft_putstr("  ");
	else
		ft_putchar(' ');
}

void	ft_print_hex(char *buffer, int i, int option)
{
	char	*base;
	char	c;
	int		j;

	base = "0123456789abcdef";
	j = 0;
	while (j < 16)
	{
		c = buffer[i + j];
		if (c != 0)
		{
			ft_putchar(base[c / 16]);
			ft_putchar(base[c % 16]);
			ft_putchar(' ');
		}
		else
			ft_putstr("   ");
		if (j == 7 && option == 1)
			ft_putstr(" ");
		j++;
	}
}

void	ft_print_ascii(char *buffer, int i)
{
	int		j;
	char	c;

	ft_putstr(" |");
	j = 0;
	while (j < 16)
	{
		c = buffer[i + j];
		if (c > 31 && c < 127)
			ft_putchar(c);
		else
			ft_putchar('.');
		j++;
	}
	ft_putstr("|");
}

void	ft_hexdump(int filedesc, char *filename, int option)
{
	int		i;
	char	*buffer;
	int		size;

	size = ft_get_filesize(filename);
	buffer = ft_get_filecontent(filedesc, size);
	i = 0;
	while (i < size)
	{
		if (i % 16 == 0)
			ft_print_address(i * 16, option);
		ft_print_hex(buffer, i, option);
		if (option == 1)
			ft_print_ascii(buffer, i);
		if (i % 16 == 0)
			ft_putchar('\n');
	}
	ft_print_address(size * 16, option);
	ft_putchar('\n');
}

int	main(int argc, char **argv)
{
	int		i;
	int		filedesc;
	int		option;

	option = 0;
	if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'C')
		option = 1;
	i = option + 1;
	while (i < argc)
	{
		filedesc = open(argv[i], O_RDONLY);
		if (filedesc >= 0)
			ft_hexdump(filedesc, argv[i], option);
		else
			ft_print_file_error(argv[i]);
		close(filedesc);
		i++;
	}
	return (0);
}
