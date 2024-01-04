/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:48:27 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/30 11:30:33 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

	sem_unlink("forks");
	sem_unlink("printing");
	sem_unlink("diying");
	table->is_printing = sem_open("printing", O_CREAT, 0666, 1);
	table->is_diying = sem_open("diying", O_CREAT, 0666, 1);
	table->forks = sem_open("forks", O_CREAT, 0666, table->count);
	i = -1;
	while (++i < table->count)
		philo_init(table->philos + i, table, i);
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
	time_usleep(100);
	sem_unlink("forks");
	sem_unlink("diying");
	sem_unlink("printing");
	free(table->philos);
	free(table);
}
