/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 09:16:28 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/19 20:42:33 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

int	main(int argc, char **argv)
{
	int		*input;
	int		input_size;
	t_tab	*tab;

	if (argc != 2)
		return (ft_print_error());
	input = ft_split(argv[1]);
	input_size = 0;
	while (input[input_size] != -1)
		input_size++;
	if (input_size % 4 != 0)
		return (ft_print_error());
	tab = ft_create_tab(input_size / 4);
	if (!tab)
		return (ft_print_error());
	ft_solve(tab, input);
	ft_print_tab(tab);
	ft_destroy_tab(tab);
	return (0);
}
