/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:54:46 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/29 15:03:29 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * La fonction ft_isdigit() vérifie que c
 * est un chiffre (de 0 à 9).
 *
 * \param	c	Un caractère non-signé.
 * \return		Un entier à valeur booléenne.
 */
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/**
 * La fonction ft_isspace() vérifie que c
 * est un caractère blanc: espace, saut de page,
 * changement de ligne, retour chariot, tabulation horizontale
 * et tabulation verticale.
 *
 * \param	c	Un caractère non-signé.
 * \return		Un entier à valeur booléenne.
 */

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\v'
		|| c == '\n' || c == '\f' || c == '\r');
}

static int	ft_atoi_overflow(int sign)
{
	if (sign < 0)
		return (0);
	return (-1);
}

/**
 * La  fonction ft_atoi() convertit le début de la chaîne pointée
 * par nptr en entier de type int.
 *
 * \param	nptr	Une chaine de caractère.
 * \return			Un entier signé de type int.
 */
int	ft_atoi(const char *nptr)
{
	unsigned long	nbr;
	int				sign;

	while (ft_isspace(*nptr))
		nptr++;
	sign = 1;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	nbr = 0;
	while (ft_isdigit(*nptr))
	{
		if ((nbr * 10 + (*nptr - '0')) / 10 != nbr)
			return (ft_atoi_overflow(sign));
		nbr *= 10;
		nbr += *nptr - '0';
		nptr++;
	}
	return (sign * nbr);
}
