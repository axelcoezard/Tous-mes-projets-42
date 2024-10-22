/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:28:10 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/29 15:33:37 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_table	*parse(int ac, char **av)
{
	t_table	*table;

	if (!check_args(ac, av))
		return (NULL);
	table = malloc(sizeof(t_table));
	table->count = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac - 1 == MAX_ARGS)
		table->min_to_eat = ft_atoi(av[MAX_ARGS]);
	else
		table->min_to_eat = -1;
	table->death = 0;
	table->philos = malloc(table->count * sizeof(t_philo));
	table->time = time_get_now();
	return (table);
}
