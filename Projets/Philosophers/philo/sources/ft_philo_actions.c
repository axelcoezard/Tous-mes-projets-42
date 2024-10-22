/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_actions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:38:56 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/29 14:14:26 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_use_fork(t_philo *philo,
			int (*mutex_action)(), char *message)
{
	mutex_action(philo->lfork);
	print(philo, message);
	mutex_action(philo->rfork);
	print(philo, message);
}

void	philo_eat(t_philo *philo)
{
	philo_use_fork(philo, pthread_mutex_lock, HAS_TAKEN_A_FORK);
	philo->last_eat = time_get_millis_now();
	print(philo, IS_EATING);
	philo->eating = 1;
	time_usleep(philo->table->time_to_eat);
	philo->eating = 0;
	philo->n_eat++;
	philo_use_fork(philo, pthread_mutex_unlock, NULL);
}

void	philo_sleep(t_philo *philo)
{
	philo->sleeping = 1;
	print(philo, IS_SLEEPING);
	time_usleep(philo->table->time_to_sleep);
	philo->sleeping = 0;
}

void	philo_think(t_philo *philo)
{
	print(philo, IS_THINKING);
}
