/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 09:15:05 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/13 09:20:20 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

int	main(int argc, char **argv)
{
	char	*arg;

	if (argc < 2)
		return (0);
	while (argc > 1)
	{
		arg = argv[argc - 1];
		write(1, arg, ft_strlen(arg));
		write(1, "\n", 1);
		argc--;
	}	
	return (0);
}
