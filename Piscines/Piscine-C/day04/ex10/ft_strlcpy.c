/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 08:49:52 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/30 16:30:36 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	src_size;

	src_size = 0;
	while (src[src_size] && src_size < size - 1)
	{
		dest[src_size] = src[src_size];
		src_size++;
	}
	dest[src_size] = '\0';
	while (src[src_size])
	{
		src_size++;
	}
	return (src_size);
}
