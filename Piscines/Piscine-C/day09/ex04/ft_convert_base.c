/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 10:03:22 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/26 02:42:16 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_atoi_base(char *str, char *base);

int	ft_check_base(char	*base)
{
	int		i;
	int		j;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		if (base[i] == ' ' || base[i] == '\n' || base[i] == '\t'
			|| base[i] == '\v' || base[i] == '\f' || base[i] == '\r')
			return (0);
		j = i + 1;
		while (base[j] != '\0')
			if (base[i] == base[j++])
				return (0);
		i++;
	}
	if (i <= 1)
		return (0);
	return (i);
}

char	*ft_getunbr_base(int nbr, char *base)
{
	long	i;
	int		j;
	int		base_size;
	int		i_size;
	char	*i_base;

	base_size = ft_check_base(base);
	if (!base_size)
		return (0);
	if (nbr < 0)
		nbr *= -1;
	i = nbr;
	i_size = 0;
	while (i > 0)
		i /= base_size, i_size++;
	i_base = malloc(i_size + 1);
	j = 0;
	while (j < i_size)
	{
		i_base[i_size - j - 1] = base[nbr % base_size];
		nbr /= base_size;
		j++;
	}
	return (i_base);
}

char	*ft_getnbr_base(int nbr, char *base)
{
	char	*unbr;
	char	*nbr_base;
	int		nbr_size;
	int		sign;
	int		j;

	unbr = ft_getunbr_base(nbr, base);
	nbr_size = 0;
	while (unbr[nbr_size])
		nbr_size++;
	sign = 0;
	if (nbr < 0)
		sign = 1;
	nbr_base = malloc(nbr_size + sign);
	if (nbr < 0)
		nbr_base[0] = '-';
	j = 0;
	while (j < nbr_size)
		nbr_base[j + sign] = unbr[j], j++;
	free(unbr);
	return (nbr_base);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		nbr_from;

	nbr_from = ft_atoi_base(nbr, base_from);
	return (ft_getnbr_base(nbr_from, base_to));
}
