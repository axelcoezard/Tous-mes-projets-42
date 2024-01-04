/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 15:53:50 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/24 16:01:28 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

double	ft_pow(double x, double power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (x * ft_pow(x, power - 1));
}
