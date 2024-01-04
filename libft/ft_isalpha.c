/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:51:59 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/14 15:16:30 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * La fonction ft_isalpha() vérifie que c 
 * est un caractère alphabétique.
 *
 * \param	c	Un caractère non-signé.
 * \return		Un entier à valeur booléenne.
 */
int	ft_isalpha(int c)
{
	return (ft_isupper(c) || ft_islower(c));
}
