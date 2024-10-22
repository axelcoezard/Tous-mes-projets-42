/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:56:16 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/13 18:57:13 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_power(int nb, int power)
{
	int	tmp;

	if (nb == 0 && power == 0)
		return (1);
	if (power < 0)
		return (0);
	tmp = 1;
	while (power-- > 0)
		tmp *= nb;
	return (tmp);
}
