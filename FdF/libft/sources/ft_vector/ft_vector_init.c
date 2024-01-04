/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:14:04 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/01 11:19:40 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_vector2	*ft_vector2_init(int x, int y)
{
	t_vector2	*vector;

	vector = malloc(sizeof(t_vector2));
	if (vector == NULL)
		return (NULL);
	vector->x = x;
	vector->y = y;
	return (vector);
}

t_vector3	*ft_vector3_init(int x, int y, int z)
{
	t_vector3	*vector;

	vector = malloc(sizeof(t_vector3));
	if (vector == NULL)
		return (NULL);
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (vector);
}
