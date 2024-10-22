/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rush.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:16:27 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/26 23:22:09 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_rush.h"

int	ft_rush(int ac, char **av)
{
	char		*path;
	t_ubignum	number;
	int			status;

	status = ft_check_args(ac, av, &path, &number);
	if (status == FT_ERROR || status == FT_DICT_ERROR)
		return (ft_print_error(status));
	if (status == FT_PARSE_INPUT)
		return (ft_parse_input());
	if (status == FT_PARSE_FILE)
	{
		return (ft_parse_file(path, number));
	}
	return (0);
}
