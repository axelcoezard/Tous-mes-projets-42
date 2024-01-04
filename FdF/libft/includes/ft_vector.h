/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:06:55 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/01 11:28:47 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include "libft.h"

struct s_vector2
{
	int	x;
	int	y;
};
typedef struct s_vector2	t_vector2;

struct s_vector3
{
	int	x;
	int	y;
	int	z;
};
typedef struct s_vector3	t_vector3;

t_vector2	*ft_vector2_init(int x, int y);
t_vector2	*ft_vector2_add(t_vector2 *a, t_vector2 *b);
t_vector2	*ft_vector2_sub(t_vector2 *a, t_vector2 *b);
t_vector2	*ft_vector2_mul(t_vector2 *a, int x);
t_vector2	*ft_vector2_div(t_vector2 *a, int x);
t_vector2	*ft_vector2_mod(t_vector2 *a, int x);
int			ft_vector2_dot(t_vector2 *a, t_vector2 *b);
int			ft_vector2_distance(t_vector2 *a, t_vector2 *b);

t_vector3	*ft_vector3_init(int x, int y, int z);
t_vector3	*ft_vector3_add(t_vector3 *a, t_vector3 *b);
t_vector3	*ft_vector3_sub(t_vector3 *a, t_vector3 *b);
t_vector3	*ft_vector3_mul(t_vector3 *a, int x);
t_vector3	*ft_vector3_div(t_vector3 *a, int x);
t_vector3	*ft_vector3_mod(t_vector3 *a, int x);
int			ft_vector3_dot(t_vector3 *a, t_vector3 *b);
int			ft_vector3_distance(t_vector3 *a, t_vector3 *b);

#endif
