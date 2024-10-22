/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:05:35 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/29 14:28:40 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

/**
 * Affiche sur la sortie standard le pid passe
 * en parametre.
 *
 * \param	pid	Le pid a afficher.
 */
static void	ft_print_pid(int pid)
{
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
}

/**
 * Execute lors de la reception dun SIGUSR1 ou SIGUSR2,
 * la fonction ft_catch_signal interprete les signaux entrants
 * et les traduit en caracteres consecutifs qu'elle affiche.
 *
 * \param	sig_id	L'id du signal recu.
 */
static void	ft_catch_signal(int sig_id, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static int				i;

	(void) context;
	i += 1;
	c |= sig_id == SIGUSR2;
	if (i < 8)
		c <<= 1;
	if (i == 8)
	{
		write(1, &c, 1);
		i = 0;
		c = 0;
	}
	usleep(200);
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_catch_signal;
	ft_print_pid(getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
