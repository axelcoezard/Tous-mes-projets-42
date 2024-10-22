/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:48:27 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/30 11:30:41 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief	La fonction threads_start prepare tous les
 * 			mutex, philosophes et threads.
 *
 * @param	table	La structure t_table contenant les
 * 					philosophes.
 *
 * @return	Une structure t_table contenenant les philosophes,
 * 			les fourchettes, et toutes les informations utiles.
 */
void	threads_start(t_table *table)
{
	size_t	i;

	pthread_mutex_init(&table->is_printing, NULL);
	pthread_mutex_init(&table->is_diying, NULL);
	i = -1;
	while (++i < table->count)
		philo_init(table->philos + i, table, i);
	i = -1;
	while (++i < table->count)
		philo_init_forks(table->philos + i, table, i);
	i = -1;
	while (++i < table->count)
	{
		pthread_create(&table->philos[i].thread, NULL, \
				philo_routine, table->philos + i);
	}
	philo_check_death(table);
}

/**
 * @brief	La fonction threads_wait attend la fin des threads
 * 			pour free(3) la memoire de t_table.
 *
 * @param	table	La structure t_table.
 */
void	threads_wait(t_table *table)
{
	size_t	i;

	time_usleep(100);
	i = -1;
	while (++i < table->count)
		pthread_mutex_destroy(table->forks + i);
	pthread_mutex_destroy(&table->is_printing);
	free(table->philos);
	free(table->forks);
	free(table);
}
