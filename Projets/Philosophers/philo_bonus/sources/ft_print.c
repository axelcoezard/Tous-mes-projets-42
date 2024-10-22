/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:38:29 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/30 11:19:44 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief	La fonction print permet d'ecrire dans le stdin
 * 			un message relatif a une action d'un philosophe.
 *
 * @param	philo	Le philosophe qui realise l'action.
 * @param	table	Le message de l'action.
 */
void	print(t_philo *philo, char *message)
{
	if (message != NULL && philo->table->is_printing != NULL)
	{
		sem_wait(philo->table->is_printing);
		if (!philo->table->death)
			printf("%zu %zu %s\n", \
				time_get_millis_from_start(philo->table), \
				philo->id, \
				message \
			);
		sem_post(philo->table->is_printing);
	}
}

int	print_err(char *where, char *message, int code)
{
	printf("philo: %s: %s\n", where, message);
	return (code);
}
