/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tail.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:06:24 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/29 09:37:10 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TAIL_H
# define FT_TAIL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <libgen.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/errno.h>

int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_strlen(char *str);
int		ft_atoi(char *str);
int		ft_is_numeric(char *str);

int		ft_print_file_error(char *exec, char *filename);
int		ft_print_offset_error(char *exec, char *offset);
int		ft_print_missing_error(char *exec);

void	ft_print_input(char	**argv);
void	ft_print_file(int i, int filedesc, int argc, char **argv);
void	ft_print_name(int i, int argc, char **argv);

#endif
