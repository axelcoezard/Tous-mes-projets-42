/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 08:55:58 by lmataris          #+#    #+#             */
/*   Updated: 2021/09/29 16:22:49 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

# include <unistd.h>

# include <stdio.h>

# include <stdlib.h>

# include <sys/errno.h>

# include <libgen.h>

# include "ft_file.h"

# include "ft_map.h"

# define FT_SOLVE_FILE	10
# define FT_SOLVE_INPUT	11
# define FT_MAP_ERROR	12
# define FT_ERROR		13

void	ft_bsq(int ac, char **av);
int		ft_check_args(int ac, char **av);
int		ft_error(int code);

void	ft_putchar(char c);
void	ft_putstr(char *str);
int		ft_strlen(char *str);
int		ft_atoi(char *str);
char	**ft_split(char	*str, char *charset);

int		ft_read_input(void);
t_map	*ft_parser(char	*path);
int		ft_parser_validate_lines(t_file *file);
char	*ft_parser_get_types(t_file *file);
t_map	*ft_parser_file(t_file	*file);

int		ft_solve(t_map *map, int x, int y, int size);

#endif
