/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:24:00 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/18 11:17:14 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_bis;
	size_t			i;

	i = 0;
	s_bis = (unsigned char *) s;
	while (i < n)
	{
		s_bis[i] = (unsigned char) c;
		i++;
	}
	return (s);
}
