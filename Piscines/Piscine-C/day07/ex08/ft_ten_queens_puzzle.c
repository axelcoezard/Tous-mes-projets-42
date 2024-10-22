/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ten_queens_puzzle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 18:51:51 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/26 07:11:05 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_ten_queens_test(int table[10], int x, int y)
{
	int		i;

	i = 0;
	while (i < x)
	{
		if (y == table[i])
			return (0);
		if (i + table[i] == x + y)
			return (0);
		if (i - table[i] == x - y)
			return (0);
		i++;
	}
	return (1);
}

void	ft_ten_queens_print(int table[10], int *count)
{
	int		i;
	char	c;

	i = 0;
	while (i < 10)
	{
		c = table[i] + '0';
		write(1, &c, 1);
		i++;
	}
	write(1, "\n", 1);
	(*count)++;
}

void	ft_ten_queens_solve(int table[10], int *count, int position)
{
	int		i;

	if (position == 10)
		ft_ten_queens_print(table, count);
	else
	{
		i = 0;
		while (i < 10)
		{
			if (ft_ten_queens_test(table, position, i))
			{
				table[position] = i;
				ft_ten_queens_solve(table, count, position + 1);
			}
			i++;
		}
	}
}

int	ft_ten_queens_puzzle(void)
{
	int		table[10];
	int		count;
	int		i;

	i = 0;
	while (i < 10)
	{
		table[i] = -1;
		i++;
	}
	count = 0;
	ft_ten_queens_solve(table, &count, 0);
	return (count);
}
