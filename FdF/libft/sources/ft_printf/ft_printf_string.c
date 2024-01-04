/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:17:59 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/27 16:41:17 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_printf_string(va_list params, t_flags flags)
{
	char	*pstr;

	(void) flags;
	pstr = (char *) va_arg(params, char *);
	if (pstr != NULL)
	{
		ft_putstr_fd(pstr, 1);
		return (ft_strlen(pstr));
	}
	ft_putstr_fd("(null)", 1);
	return (6);
}
