/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelcoezard <axelcoezard@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:17:59 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/11 22:39:31 by axelcoezard      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_printf_string(va_list params, char flag)
{
	char	*pstr;

	(void) flag;
	pstr = (char *) va_arg(params, char *);
	if (pstr != NULL)
	{
		ft_putstr_fd(pstr, 1);
		return (ft_strlen(pstr));
	}
	ft_putstr_fd("(null)", 1);
	return (6);
}
