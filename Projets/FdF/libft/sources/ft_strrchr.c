/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:02:29 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/23 17:18:37 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *) s;
	i = ft_strlen(s);
	while (str[i] != (unsigned char) c)
	{
		if (i == 0)
			return (NULL);
		i--;
	}
	return (str + i);
}
