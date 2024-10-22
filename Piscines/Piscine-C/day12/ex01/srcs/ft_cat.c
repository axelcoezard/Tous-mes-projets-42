/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:53:36 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/25 13:27:32 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_cat.h"

int	ft_print_error(char *exec, char *filename)
{
	ft_putstr(basename(exec));
	ft_putstr(": ");
	ft_putstr(filename);
	ft_putstr(": ");
	ft_putstr(strerror(errno));
	ft_putstr("\n");
	return (0);
}

int	ft_read(int filedesc, char *buffer, char *exec, char *filename)
{
	int		state;

	state = read(filedesc, buffer, 1);
	if (state == -1)
		return (ft_print_error(exec, filename));
	return (state);
}

int	ft_read_file(char **argv, int i)
{
	char	buffer;
	int		filedesc;

	filedesc = open(argv[i], O_RDONLY);
	if (filedesc < 0)
		return (ft_print_error(argv[0], argv[i]));
	while (ft_read(filedesc, &buffer, argv[0], argv[i]) != 0)
		ft_putchar(buffer);
	close(filedesc);
	return (0);
}

int	ft_read_input(void)
{
	char	buffer;

	while (read(STDIN_FILENO, &buffer, 1) != 0)
		ft_putchar(buffer);
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;

	if (argc < 2 || (argv[1][0] == '-' && argv[1][1] == '\0'))
		return (ft_read_input());
	i = 0;
	while (i < argc - 1)
		ft_read_file(argv, i + 1), i++;
	return (0);
}
