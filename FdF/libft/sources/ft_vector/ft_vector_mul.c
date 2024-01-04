/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_mul.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:49:28 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/01 11:21:22 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_vector2	*ft_vector2_mul(t_vector2 *a, int x)
{
	if (a == NULL)
		return (NULL);
	a->x *= x;
	a->y *= x;
	return (a);
}

t_vector3	*ft_vector3_mul(t_vector3 *a, int x)
{
	if (a == NULL)
		return (NULL);
	a->x *= x;
	a->y *= x;
	a->z *= x;
	return (a);
}
