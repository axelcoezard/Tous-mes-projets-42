/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:39:22 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/30 11:46:31 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/* ************************* INCLUDES ************************* */
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <semaphore.h>

/* ************************* DEFINES ************************** */
# define MIN_ARGS			4
# define MAX_ARGS			5

# define HAS_TAKEN_A_FORK	"has taken a fork"
# define IS_EATING			"is eating"
# define IS_SLEEPING		"is sleeping"
# define IS_THINKING		"is thinking"
# define HAS_DIED			"died"

/* ************************ STRUCTURES ************************ */
typedef struct s_philo
{
	size_t			id;
	pthread_t		thread;

	int				eating;
	size_t			last_eat;
	int				n_eat;
	int				sleeping;

	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	sem_t			*forks;
	t_philo			*philos;
	size_t			count;

	size_t			time_to_sleep;
	size_t			time_to_eat;
	size_t			time_to_die;
	int				min_to_eat;
	int				death;

	struct timeval	time;
	sem_t			*is_diying;
	sem_t			*is_printing;
}	t_table;

/* ********************** INPUT / OUTPUT ********************** */
void			print(t_philo *philo, char *message);
int				print_err(char *where, char *message, int code);

/* ************************** LIBFT *************************** */
int				ft_isdigit(int c);
int				ft_isspace(int c);
int				ft_atoi(const char *nptr);

/* ********************** CHECK / PARSE *********************** */
int				check_args(int ac, char **av);
int				check_int(const char *nptr);
int				check_negative(const char *nptr);
t_table			*parse(int ac, char **av);

/* ************************* THREADS ************************** */
void			threads_start(t_table *table);
void			threads_wait(t_table *table);

/* ************************** PHILOS ************************** */
void			philo_init(t_philo *philo, t_table *table, int id);
void			philo_init_forks(t_philo *philo, t_table *table, int id);
void			*philo_routine(void *data);
void			philo_use_fork(t_philo *philo,
					int (*mutex_action)(), char *msg);
void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_think(t_philo *philo);
size_t			philo_check_eat(t_table *table);
void			philo_check_death(t_table *table);

/* *************************** TIME *************************** */
struct timeval	time_get_now(void);
size_t			time_get_millis(struct timeval time);
size_t			time_get_millis_now(void);
size_t			time_get_millis_from_start(t_table *table);
void			time_usleep(size_t	usec);

#endif
