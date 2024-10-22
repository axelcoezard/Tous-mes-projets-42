/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cat.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:06:51 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/24 12:21:46 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CAT_H
# define FT_CAT_H

# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <libgen.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/errno.h>

int		ft_putchar(char c);
int		ft_putstr(char *str);

int		ft_print_error(char *exec, char *message);

#endif
