/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 21:08:08 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/25 19:24:00 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <signal.h>

# define EXIT_SUCCESS		0
# define EXIT_ERROR			1

# define MESSAGE_SENT		0
# define MESSAGE_RECEIVED	1

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);

#endif
