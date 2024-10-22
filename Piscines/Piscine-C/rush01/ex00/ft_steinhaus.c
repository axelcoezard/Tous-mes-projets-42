/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_steinhaus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 17:35:23 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/19 22:41:20 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

typedef struct s_cursors {
	int		left;
	int		right;	
}				t_cursors;

int	*ft_contraint_exists(int *cons, t_cursors *c, int off, int dist)
{
	int		*found;
	int		i;
	
	found = malloc(dist *sizeof(int));
	i = 0;
	while (i < dist)
		found[i++] = 0;
	i = 0;
	while (i < dist)
	{
		if (c->left == cons[off + i] && c->right == cons[off + i + dist])
		{
			found[i] = 1;
		}
		i++;
	}
	return (found);
}

int	*ft_horizontal_check(int *row, int *contraints, int n)
{
	t_cursors *cursors;
	int		pos;
	int		max;

	cursors = malloc(sizeof(t_cursors));
	pos = 0;
	cursors->left = 1;
	max = row[0];
	while (pos < n - 1)
	{
		if (max < row[pos + 1])
			max = row[pos + 1], cursors->left++;
		pos++;
	}
	pos = n - 1;
	cursors->right = 1;
	max = row[n - 1];
	while (pos > 0)
	{
		if (max < row[pos - 1])
			max = row[pos - 1], cursors->right++;
		pos--;
	}
	return (ft_contraint_exists(contraints, cursors, 2 * n, n));
}

int	*ft_vertical_check(int *col, int *contraints, int n)
{
	t_cursors *cursors;
	int		pos;
	int		max;

	cursors = malloc(sizeof(t_cursors));
	pos = 0;
	cursors->left = 1;
	max = col[0];
	while (pos < n - 1)
	{
		if (max < col[pos + 1])
			max = col[pos + 1], cursors->left++;
		pos++;
	}
	pos = n - 1;
	cursors->right = 1;
	max = col[n - 1];
	while (pos > 0)
	{
		if (max < col[pos - 1])
			max = col[pos - 1], cursors->right++;
		pos--;
	}
	return (ft_contraint_exists(contraints, cursors, 0, n));
}
