/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:09:41 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/18 11:22:21 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Alloue et retourne une copie de la chaine ’s1’,
 * sans les caractères spécifiés dans ’set’ au début
 * et à la fin de la chaine de caractères.
 *
 * \param	s1	La chaine de caractères à trimmer.
 * \param	set	Le set de reference de caractères à trimmer.
 * \return		La chaine de caractères trimmée.
 */
char	*ft_strtrim(const char *s1, const char *set)
{
	int		size;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	size = ft_strlen(s1);
	while (size && ft_strchr(set, s1[size]))
		size--;
	return (ft_substr(s1, 0, size + 1));
}
