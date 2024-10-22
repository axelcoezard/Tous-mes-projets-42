/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:53:36 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/24 08:59:18 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_display_file.h"

int	ft_print_error(char *message)
{
	ft_putstr(message);
	ft_putchar('\n');
	return (0);
}

int	main(int argc, char **argv)
{
	char	buffer;
	char	*filename;
	int		filedesc;
	int		filesize;

	if (argc == 1)
		return (ft_print_error("File name missing."));
	if (argc > 2)
		return (ft_print_error("Too many arguments."));
	filename = argv[1];
	filedesc = open(filename, O_RDONLY);
	if (filedesc < 0)
		return (ft_print_error("Cannot read file."));
	filesize = 0;
	while (read(filedesc, &buffer, 1) != 0)
	{
		ft_putchar(buffer);
		filesize++;
	}
	close(filedesc);
	return (0);
}
