/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:25:05 by acoezard          #+#    #+#             */
/*   Updated: 2023/04/24 11:25:14 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

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
