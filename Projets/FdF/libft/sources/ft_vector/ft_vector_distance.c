/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_distance.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:43:37 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/01 11:15:27 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_vector2_distance(t_vector2 *a, t_vector2 *b)
{
	int	xx;
	int	yy;

	if (a == NULL || b == NULL)
		return (0);
	xx = b->x - a->x;
	yy = b->y - a->y;
	return (ft_sqrt(ft_pow(xx, 2) + ft_pow(yy, 2)));
}

int	ft_vector3_distance(t_vector3 *a, t_vector3 *b)
{
	int	xx;
	int	yy;
	int	zz;

	if (a == NULL || b == NULL)
		return (0);
	xx = b->x - a->x;
	yy = b->y - a->y;
	zz = b->z - a->z;
	return (ft_sqrt(ft_pow(xx, 2) + ft_pow(yy, 2) + ft_pow(zz, 2)));
}
