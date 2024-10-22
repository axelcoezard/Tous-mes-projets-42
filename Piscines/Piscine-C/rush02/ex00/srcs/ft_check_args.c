/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:38:11 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/26 23:14:19 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_rush.h"

int	ft_check_args(int ac, char **av, char **path, t_ubignum *number)
{
	char		*input;
	t_bignum	tmp;

	if (ac < 2)
		return (FT_PARSE_INPUT);
	if (ac > 3)
		return (FT_DICT_ERROR);
	*path = "numbers_en.dict";
	if (ac == 3)
	{
		*path = av[1];
		input = av[2];
	}
	else
		input = av[1];
	if (!ft_is_numeric(input))
		return (FT_ERROR);
	if (ft_strlen(input) > 40)
		return (FT_ERROR);
	tmp = ft_atoi(input);
	if (tmp < 0)
		return (FT_ERROR);
	*number = tmp;
	return (FT_PARSE_FILE);
}
