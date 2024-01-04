/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_dot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:38:57 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/01 11:16:43 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_vector2_dot(t_vector2 *a, t_vector2 *b)
{
	if (a == NULL || b == NULL)
		return (0);
	return (a->x * b->x + a->y * b->y);
}

int	ft_vector3_dot(t_vector3 *a, t_vector3 *b)
{
	if (a == NULL || b == NULL)
		return (0);
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}
