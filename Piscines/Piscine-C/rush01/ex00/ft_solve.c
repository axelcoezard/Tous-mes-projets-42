/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:56:36 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/19 23:31:29 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

int	ft_solve(t_tab *tab, int *input)
{
	int		size;
	int 	i;
	int		j;
	int		n;
	int		**pot;

	(void) tab;
	size = 0;
	while (input[size] != -1)
		size++;
	pot = ft_trotter(size / 4, input);
	n = size / 4;
	i = 0;	
	while (i < 2 * n)
	{
		j = 0;
		while (pot[i][j] != 0)
		{
			printf("%d", pot[i][j]);
			j++;
		}
		printf("\n");
		i++;	
	}		
	return (0);
}
