/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:29:06 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/21 11:42:49 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_get_line(char *backup)
{
	char	*line;
	int		backup_size;
	int		rest_size;

	if (backup == NULL)
		return (NULL);
	backup_size = ft_strlen(backup);
	rest_size = ft_strlen(ft_strchr(backup, '\n')) - 1;
	line = (char *) malloc(backup_size - rest_size + 1);
	ft_strlcpy(line, backup, backup_size - rest_size + 1);
	return (line);
}

static char	*gnl_reset_backup(char *backup, char *line)
{
	char	*n_backup;
	int		backup_size;
	int		line_size;

	if (backup == NULL || line == NULL)
		return (NULL);
	backup_size = ft_strlen(backup);
	line_size = ft_strlen(line);
	if (line_size <= 0)
	{
		free(backup);
		return (NULL);
	}
	n_backup = malloc(backup_size - line_size + 1);
	ft_strlcpy(n_backup, backup + line_size, backup_size - line_size + 1);
	free(backup);
	return (n_backup);
}

static char	*gnl_extend_backup(char *backup, char *bytes)
{
	char	*n_backup;
	int		backup_size;
	int		bytes_size;

	if (backup == NULL || bytes == NULL)
		return (NULL);
	backup_size = ft_strlen(backup);
	bytes_size = ft_strlen(bytes);
	n_backup = (char *) malloc(backup_size + bytes_size + 1);
	ft_strlcpy(n_backup, backup, backup_size + 1);
	ft_strcat(n_backup, bytes);
	free(backup);
	return (n_backup);
}

static char	*gnl_get_until_newline(int fd, char *backup)
{
	char	*bytes;
	int		reader;

	bytes = (char *) malloc(BUFFER_SIZE + 1);
	if (!bytes)
	{
		free(bytes);
		free(backup);
		return (NULL);
	}
	reader = 1;
	while (!ft_strchr(backup, '\n') && reader != 0)
	{
		reader = read(fd, bytes, BUFFER_SIZE);
		if (reader == -1)
		{
			free(backup);
			free(bytes);
			return (NULL);
		}
		bytes[reader] = 0;
		backup = gnl_extend_backup(backup, bytes);
	}
	free(bytes);
	return (backup);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!backup)
		backup = ft_strdup("");
	backup = gnl_get_until_newline(fd, backup);
	if (backup == NULL)
		return (NULL);
	line = gnl_get_line(backup);
	backup = gnl_reset_backup(backup, line);
	if (line[0] == '\0')
	{
		free(backup);
		free(line);
		return (NULL);
	}
	return (line);
}
