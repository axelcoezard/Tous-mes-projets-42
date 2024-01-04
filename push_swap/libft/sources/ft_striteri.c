/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelcoezard <axelcoezard@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:58:56 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/12 22:11:09 by axelcoezard      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/**
 * Applique la fonction f à chaque caractère de la
 * chaîne de caractères transmise comme argument, et
 * en passant son index comme premier argument. Chaque
 * caractère est transmis par adresse à f pour être
 * modifié si nécessaire.
 *
 * \param	s	La chaine de caractères sur laquelle itérer.
 * \param	f	La fonction à appliquer à chaque caractère.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s && s[i] != 0)
	{
		f(i, s + i);
		i++;
	}
}
