/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:41:23 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/18 16:38:33 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*sptr;
	size_t			i;

	sptr = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (sptr[i] == (unsigned char) c)
			return (sptr + i);
		i++;
	}
	return (NULL);
}
