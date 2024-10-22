/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 16:42:39 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/13 18:56:42 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	float	a;
	float	b;
	int		precision;

	a = nb;
	b = nb;
	precision = 1000000;
	while (precision > 0)
	{
		b = b + a / b;
		b /= 2;
		precision--;
	}
	if (b - (int) b != 0)
		return (0);
	return (b);
}
