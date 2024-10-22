/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 18:42:49 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/24 09:07:59 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_hexdump.h"

int	ft_get_filesize(char *filename)
{
	int		size;
	int		filedesc;
	char	buffer;

	size = 0;
	filedesc = open(filename, O_RDONLY);
	while (read(filedesc, &buffer, 1) != 0)
		size++;
	close(filedesc);
	return (size);
}

char	*ft_get_filecontent(int filedesc, int filesize)
{
	char	*content;
	char	buffer;

	content = malloc(filesize + 1);
	filesize = 0;
	while (read(filedesc, &buffer, 1) != 0)
		content[filesize] = buffer, filesize++;
	return (content);
}
