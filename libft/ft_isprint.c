/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:06:16 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/14 15:16:49 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * La fonction ft_isprint() vérifie que c 
 * est un caractère imprimable, y compris l'espace.
 *
 * \param	c	Un caractère non-signé.
 * \return		Un entier à valeur booléenne.
 */

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
