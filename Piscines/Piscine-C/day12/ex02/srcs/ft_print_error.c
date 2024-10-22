/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 18:41:21 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/27 19:09:56 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_tail.h"

int	ft_print_file_error(char *exec, char *filename)
{
	ft_putstr(basename(exec));
	ft_putstr(": ");
	ft_putstr(filename);
	ft_putstr(": ");
	ft_putstr(strerror(errno));
	ft_putstr("\n");
	return (1);
}

int	ft_print_offset_error(char *exec, char *offset)
{
	ft_putstr(basename(exec));
	ft_putstr(": illegal offset -- ");
	ft_putstr(offset);
	ft_putstr("\n");
	return (1);
}

int	ft_print_missing_error(char *exec)
{
	ft_putstr(basename(exec));
	ft_putstr(": option requires an argument -- c\n");
	ft_putstr("usage: ");
	ft_putstr(basename(exec));
	ft_putstr(" [-F | -f | -r] [-q] [-b # | -c # | -n #] [file ...]\n");
	return (1);
}
