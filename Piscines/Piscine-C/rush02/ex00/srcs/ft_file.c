/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:32:12 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/26 23:21:27 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_rush.h"

int	ft_read(int filedesc, char *buffer, int size)
{
	int		status;

	status = read(filedesc, buffer, size);
	if (status < 0)
		return (ft_print_error(FT_DICT_ERROR));
	return (status);
}

int	get_file_size(char *filepath)
{
	int		filedesc;
	int		size;
	char	c;

	size = 0;
	filedesc = open(filepath, O_RDONLY);
	if (filedesc < 0)
		return (ft_print_error(FT_DICT_ERROR));
	while (ft_read(filedesc, &c, 1) != 0)
		size++;
	close(filedesc);
	return (size);
}

int	get_file_buffer(char *filepath, char **buffer)
{
	int		filesize;
	int		filedesc;
	char	c;
	char	*nbuffer;

	filesize = get_file_size(filepath);
	if (filesize == 0)
		return (0);
	filedesc = open(filepath, O_RDONLY);
	nbuffer = malloc(filesize + 1);
	if (filedesc < 0)
		return (ft_print_error(FT_DICT_ERROR));
	filesize = 0;
	while (ft_read(filedesc, &c, 1) != 0)
		nbuffer[filesize] = c, filesize++;
	nbuffer[filesize] = 0;
	close(filedesc);
	*buffer = nbuffer;
	return (1);
}

char	**get_file_lines(char *filepath)
{
	char	*buffer;
	char	**lines;

	if (get_file_buffer(filepath, &buffer))
	{
		lines = ft_split(buffer, "\n");
		free(buffer);
		return (lines);
	}
	if (buffer)
		free(buffer);
	return (NULL);
}	
