/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 10:07:35 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/27 15:35:20 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILE_H
# define FT_FILE_H

# include <fcntl.h>

# include <sys/types.h>

# include <sys/stat.h>

typedef struct s_file {
	char	*path;
	char	*buffer;
	char	**lines;
	int		descriptor;
	int		size;
}				t_file;

t_file	*ft_file_open(char	*path, int code);

int		ft_file_size(t_file *file);

int		ft_file_read(t_file *file);

int		ft_file_close(t_file *file);

#endif
