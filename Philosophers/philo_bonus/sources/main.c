/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:38:33 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/29 15:02:48 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_table	*table;

	table = parse(ac, av);
	if (table != NULL)
	{
		threads_start(table);
		threads_wait(table);
	}
	return (0);
}
