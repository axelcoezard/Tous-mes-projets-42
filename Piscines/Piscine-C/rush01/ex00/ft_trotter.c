/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trotter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 18:43:36 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/19 23:19:33 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

int	**ft_trotter_init(int n)
{
	int		**pot;
	int		i;
	int		j;

	pot = malloc(sizeof(int *) * n * 2);
	if (!pot)
		return (NULL);
	i = 0;
	while (i < n * 2)
	{
		pot[i] = malloc(1600000 * n);
		if (!pot[i])
			return (NULL);
		j = 0;
		while (j < 400000 * n)
			pot[i][j] = 0, j++;
		i++;
	}
	return (pot);
}

int	ft_trotter_zero(int *row)
{
	int		i;

	i = 0;
	while (row[i] != 0)
		i++;
	return (i);
}

int	ft_trotter_devide(int n, t_params *params, int *contraints, int **pot)
{
	int		i;
	int		j;
	int		*row_to_append;
	int		*col_to_append;
	int		tmp;

	row_to_append = ft_horizontal_check(params->a, contraints, n);
	col_to_append = ft_vertical_check(params->a, contraints, n);
	i = 0;
	while (i < n)
	{
		tmp = ft_trotter_zero(pot[i]);
		j = 0;
		while (row_to_append[i] == 1 && j < n)
			pot[i][tmp + j] = params->a[j], j++;
		i++;
	}	
	i = 0;
	while (i < n)
	{
		tmp = ft_trotter_zero(pot[i + n]);
		j = 0;
		while (col_to_append[i] == 1 && j < n)
			pot[i + n][tmp + j] = params->a[j], j++;
		i++;
	}
	return (0);
}

int	ft_trotter_spread(t_params *params, int **pot, int n, int *contraints)
{
	int		i;
	int		*tmp;

	i = 0;
	while (i < n)
	{
		params->a[i] = i + 1;
		params->dir[i++] = 0;
	}
	ft_trotter_devide(n, params, contraints, pot);
	i = 1;
    while (i < ft_factorial(n))
	{
		tmp = malloc(n * sizeof(int));
		tmp = ft_johnson(params, n);
		ft_trotter_devide(n, params, contraints, pot);	   	
		i++;
	}
	return (0);
}

int	**ft_trotter(int n, int *contraints)
{
	t_params	*params;
	int			**pot;
	
	params = malloc(sizeof(t_params));
	params->a = malloc(sizeof(int) * n);
	params->dir = malloc(sizeof(int) * n);
	pot = ft_trotter_init(n);
	if (!pot || !params || !params->a || !params->dir)
		return (NULL);
	ft_trotter_spread(params, pot, n, contraints);
	free(params->a);
	free(params->dir);
	free(params);
	return (pot);
}
