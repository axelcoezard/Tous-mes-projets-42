/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:51:39 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/18 11:11:40 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_size;
	size_t	src_size;
	size_t	res;

	dest_size = ft_strlen(dest);
	src_size = ft_strlen(src);
	if (size <= dest_size)
		return (src_size + size);
	res = src_size + dest_size;
	src_size = 0;
	while (src[src_size] && dest_size + 1 < size)
		dest[dest_size++] = src[src_size++];
	dest[dest_size] = 0;
	return (res);
}
