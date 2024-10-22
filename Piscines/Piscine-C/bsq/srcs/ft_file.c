/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 10:16:45 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/30 09:20:14 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft.h"

int	ft_read(int descriptor, char *buffer)
{
	int	status;

	status = read(descriptor, buffer, 1);
	if (status < 0)
		return (0);
	return (status);
}

t_file	*ft_file_open(char	*path, int code)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	file->path = path;
	file->descriptor = open(path, code);
	if (file->descriptor < 0)
		return (NULL);
	return (file);
}

int	ft_file_size(t_file	*file)
{
	int		descriptor;
	int		size;
	char	buffer;

	size = 0;
	descriptor = open(file->path, O_RDWR);
	if (descriptor >= 0)
	{
		while (ft_read(descriptor, &buffer) != 0)
			size++;
	}
	close(descriptor);
	return (size);
}

int	ft_file_read(t_file *file)
{
	char	buffer;
	int		i;

	if (!file)
		return (ft_error(FT_MAP_ERROR));
	if (!file->path)
		return (ft_error(FT_MAP_ERROR));
	file->size = ft_file_size(file);
	if (!file->size)
		return (ft_error(FT_MAP_ERROR));
	if (!file->descriptor)
		return (ft_error(FT_MAP_ERROR));
	file->buffer = malloc(file->size + 1);
	i = 0;
	while (ft_read(file->descriptor, &buffer) != 0)
		file->buffer[i++] = buffer;
	close(file->descriptor);
	file->buffer[file->size] = '\0';
	file->lines = ft_split(file->buffer, "\n");
	return (1);
}

int	ft_file_close(t_file *file)
{
	int	i;

	if (file->descriptor)
		close(file->descriptor);
	if (file)
	{
		if (file->buffer)
			free(file->buffer);
		if (file->lines)
		{
			i = 0;
			while (file->lines[i] != NULL)
				free(file->lines[i]), i++;
			free(file->lines);
		}
		free(file);
	}
	return (1);
}
