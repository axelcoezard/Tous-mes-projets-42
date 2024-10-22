/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:47:57 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/30 11:46:43 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_init(t_philo *philo, t_table *table, int index)
{
	philo->id = index + 1;
	philo->table = table;
	philo->sleeping = 0;
	philo->eating = 0;
	philo->last_eat = time_get_millis_now();
	philo->n_eat = 0;
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	if (philo->id % 2 == 0)
		time_usleep(10);
	while (!philo->table->death)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

size_t	philo_check_eat(t_table *table)
{
	size_t	i;

	if (table->min_to_eat < 0)
		return (0);
	i = -1;
	while (++i < table->count)
	{
		if (table->philos[i].n_eat < table->min_to_eat)
			return (0);
	}
	return (1);
}

void	philo_check_death(t_table *table)
{
	size_t	i;

	if (table->count == 1)
		print(table->philos, HAS_DIED);
	while (table->count > 1)
	{
		i = -1;
		while (++i < table->count)
		{
			if (table->philos[i].eating)
				continue ;
			sem_wait(table->is_diying);
			if (time_get_millis_now() - \
			table->philos[i].last_eat >= table->time_to_die)
			{
				print(table->philos + i, HAS_DIED);
				table->death = 1;
				return ;
			}
			sem_post(table->is_diying);
		}
		if (philo_check_eat(table))
			break ;
	}
	table->death = 1;
}
