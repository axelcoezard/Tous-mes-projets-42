/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_johnson.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 22:14:35 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/19 23:42:02 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

int	ft_search_tab(int *a, int n, int mobile)
{
	int		i;

	i = 0;
	while (i < n)
	{
		if (a[i] == mobile)
			return (i + 1);
		i++;
	}
	return (0);
}

int	ft_get_mobile(int *a, int *dir, int n)
{
	int		mobile_prev;
	int		mobile;
	int		i;

	mobile_prev = 0;
	mobile = 0;
	i = 0;
	while (i < n)
	{
		if (dir[a[i] - 1] == 0 && i != 0)
			if (a[i] > a[i - 1]  && a[i] > mobile_prev)
				mobile = a[i], mobile_prev = mobile;
		if (dir[a[i] - 1] == 1 && i != n - 1)
			if (a[i] > a[i + 1] && a[i] > mobile_prev)
				mobile = a[i], mobile_prev = mobile;
		i++;
	}
	if (mobile == 0 && mobile_prev == 0)
		return (0);
	return (mobile);
}

int	*ft_johnson(t_params *params, int n)
{
	int		mobile;
	int		pos;
	int		i;

	mobile = ft_get_mobile(params->a, params->dir, n);
	pos = ft_search_tab(params->a, n, mobile);
	if (params->dir[params->a[pos - 1] - 1] == 0)
       ft_swap(&params->a[pos-1], &params->a[pos-2]);
    else if (params->dir[params->a[pos - 1] - 1] == 1)
       ft_swap(&params->a[pos], &params->a[pos-1]);
	i = 0;
	while (i < n)
	{
		if (params->a[i] > mobile)
		{
			if (params->dir[params->a[i] - 1] == 0)
                params->dir[params->a[i] - 1] = 1;
            else if (params->dir[params->a[i] - 1] == 1)
                params->dir[params->a[i] - 1] = 0;
		}
		i++;
	}
	return (params->a);
}
