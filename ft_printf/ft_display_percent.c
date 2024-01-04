/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_percent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:09:10 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/19 14:27:25 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_display_percent(va_list params, t_flags flags)
{
	(void) params;
	(void) flags;
	ft_putchar_fd('%', 1);
	return (1);
}
