/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:53:36 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/29 09:31:56 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_tail.h"

int	main(int argc, char **argv)
{
	int		i;
	int		filedesc;

	if (argc < 3)
		return (ft_print_missing_error(argv[0]));
	if (!ft_is_numeric(argv[2]))
		return (ft_print_offset_error(argv[0], argv[2]));
	if (argc < 4)
	{
		ft_print_input(argv);
		return (0);
	}
	i = 3;
	while (i < argc)
	{
		filedesc = open(argv[i], O_RDONLY);
		if (filedesc >= 0)
			ft_print_file(i, filedesc, argc, argv);
		else
			ft_print_file_error(argv[0], argv[i]);
		close(filedesc);
		i++;
	}
	return (0);
}
