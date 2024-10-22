/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:36:16 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/01 11:21:49 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_vector2	*ft_vector2_sub(t_vector2 *a, t_vector2 *b)
{
	if (a == NULL || b == NULL)
		return (NULL);
	a->x -= b->x;
	a->y -= b->y;
	return (a);
}

t_vector3	*ft_vector_sub(t_vector3 *a, t_vector3 *b)
{
	if (a == NULL || b == NULL)
		return (NULL);
	a->x -= b->x;
	a->y -= b->y;
	a->z -= b->z;
	return (a);
}
