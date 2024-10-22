/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rush.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:26:14 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/26 22:23:46 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RUSH_H
# define FT_RUSH_H

# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <libgen.h>

# ifdef __SIZEOF_INT128__

typedef unsigned __int128	t_ubignum;
typedef __int128			t_bignum;
# else

typedef uint64_t			t_ubignum;
typedef int64_t				t_bignum;
# endif 

# define FT_PARSE_INPUT	10
# define FT_PARSE_FILE	11
# define FT_ERROR		12
# define FT_DICT_ERROR	13

typedef struct s_entry
{
	t_ubignum	n;
	char		*str;
}	t_entry;

void		ft_putchar(char c);
void		ft_putstr(char *str);
t_bignum	ft_atoi(char *str);
int			ft_is_numeric(char *str);

char		**ft_split(char *str, char *delimiters);

t_entry		**split_dict_entry(char **lines);
int			free_dict_entries(t_entry	**entries);
char		**get_file_lines(char *filepath);

int			ft_rush(int ac, char **av);
int			ft_check_args(int ac, char **av, char **path, t_ubignum *input);

int			ft_parse_input(void);
int			ft_parse_file(char *filepath, t_ubignum number);
int			ft_print_error(int code);

t_entry		*get_entry_first_dividing(t_entry **entries, t_ubignum number);
t_entry		*get_entry_by_n(t_entry **entries, t_ubignum n);

int			ft_strlen(char *s);
char		*ft_strdup(char *src);
int			get_count(char **lines);
int			ft_free(char **line);

#endif
