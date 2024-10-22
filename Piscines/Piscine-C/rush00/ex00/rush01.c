/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:47:43 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/15 10:28:52 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

void	draw_row(int x, char start, char middle, char end)
{
	int		middle_x;

	ft_putchar(start);
	if (x >= 3)
	{
		middle_x = 2;
		while (middle_x < x)
		{
			ft_putchar(middle);
			middle_x++;
		}
	}
	if (x >= 2)
		ft_putchar(end);
	ft_putchar('\n');
}

void	rush(int x, int y)
{
	int		middle_y;

	if (x >= 0 ||  y >= 0)
	{
		draw_row(x, '/', '*', '\\');
		if (y >= 3)
		{
			middle_y = 2;
			while (middle_y < y)
			{
				draw_row(x, '*', ' ', '*');
				middle_y++;
			}
		}	
		if (y >= 2)
			draw_row(x, '\\', '*', '/');
	}
}
