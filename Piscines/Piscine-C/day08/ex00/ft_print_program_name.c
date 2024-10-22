/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_program_name.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 09:07:35 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/13 11:55:30 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int		count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

int	main(int argc, char **argv)
{
	(void) argc;
	write(1, argv[0], ft_strlen(argv[0]));
	write(1, "\n", 1);
}
