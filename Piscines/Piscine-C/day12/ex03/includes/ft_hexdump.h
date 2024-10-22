/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:50:49 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/28 10:59:26 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEXDUMP_H
# define FT_HEXDUMP_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

int		ft_putchar(char c);
int		ft_putstr(char *str);

char	*ft_strcpy(char *dest, char *src, int len);
char	*ft_strdup(char *src, int len);
int		ft_strcmp(char *s1, char *s2);

int		ft_print_file_error(char *filename);

void	ft_hexdump(int filedesc, char *filename, int option);
int		ft_get_filesize(char *filename);
char	*ft_get_filecontent(int filedesc, int filesize);

#endif
