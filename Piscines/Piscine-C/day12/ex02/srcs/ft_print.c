/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 18:42:49 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/29 10:05:45 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_tail.h"

void	ft_print_name(int i, int argc, char **argv)
{
	int	j;

	j = 0;
	if (argc > 4)
	{
		if (i > 3)
			write(1, "\n==> ", 5);
		else
			write(1, "==> ", 4);
		while (argv[i][j])
		{
			write(1, &argv[i][j], 1);
			j++;
		}
		write(1, " <==\n", 5);
	}	
}

int	ft_read(int desc, char *buffer, int size)
{
	int		status;

	status = read(desc, buffer, size);
	if (status < 0)
		status = 0;
	return (status);
}

void	ft_print_input(char	**argv)
{
	char	c;
	char	*buffer;
	int		offset;
	int		j;

	offset = ft_atoi(argv[2]);
	if (offset < 0)
		offset *= -1;
	buffer = malloc(sizeof(char) * (offset + 1));
	while (ft_read(STDIN_FILENO, &c, 1) != 0)
	{
		j = 1;
		while (j < offset + 1)
			buffer[j - 1] = buffer[j], j++;
		buffer[offset] = c;
	}
	buffer[offset] = '\0';
	ft_putstr(buffer);
	if (offset > 0 && ft_strlen(buffer) > 0)
		ft_putchar('\n');
	free(buffer);
}

void	ft_print_file(int i, int filedesc, int argc, char **argv)
{
	char	buffer;
	int		offset;
	int		filesize;
	int		fd2;

	offset = ft_atoi(argv[2]);
	if (offset < 0)
		offset *= -1;
	filesize = 0;
	fd2 = open(argv[i], O_RDWR);
	if (fd2 >= 0)
		while (read(fd2, &buffer, 1) != 0)
			filesize++;
	close(fd2);
	ft_print_name(i, argc, argv);
	if (filesize > 0)
	{
		fd2 = 0;
		while (read(filedesc, &buffer, 1) != 0)
			if (fd2++ >= filesize - offset)
				ft_putchar(buffer);
	}
}
