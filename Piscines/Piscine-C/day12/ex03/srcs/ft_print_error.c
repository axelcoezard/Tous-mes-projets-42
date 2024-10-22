/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 18:41:21 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/24 09:08:15 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_hexdump.h"

int	ft_print_file_error(char *filename)
{
	ft_putstr("ft_hexdump: ");
	ft_putstr(filename);
	ft_putstr(": No such file or directory\n");
	return (0);
}
