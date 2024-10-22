/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 14:07:38 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/26 10:31:28 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_print_comb(int table[10], int n)
{
	int		i;

	i = 0;
	while (i < n)
		ft_putchar(table[i] + '0'), i++;
	if (table[0] != 10 - n)
		write(1, ", ", 2);
}

void	ft_solve_combn(int table[10], int n, int i)
{
	if (i == 0)
		table[i] = 0;
	else
		table[i] = table[i - 1] + 1;
	while (table[i] < 11 - n + i)
	{
		if (i == n - 1)
			ft_print_comb(table, n);
		else
			ft_solve_combn(table, n, i + 1);
		table[i] += 1;
	}
}

void	ft_print_combn(int n)
{
	int		table[10];

	ft_solve_combn(table, n, 0);
}
