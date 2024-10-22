/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 08:33:53 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/23 08:35:57 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	int		size;

	size = 0;
	while (str[size])
		size++;
	return (size);
}

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	dest_size;
	unsigned int	src_size;
	unsigned int	res;

	dest_size = ft_strlen(dest);
	src_size = ft_strlen(src);
	if (size <= dest_size)
		return (src_size + size);
	res = src_size + dest_size;
	src_size = 0;
	while (src[src_size] != '\0' && dest_size + 1 < size)
		dest[dest_size++] = src[src_size++];
	dest[dest_size] = '\0';
	return (res);
}
