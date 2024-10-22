/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:50:49 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/21 15:23:54 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DO_OP_H
# define DO_OP_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

int		ft_putchar(char c);
int		ft_putstr(char *str);
void	ft_putnbr(int nbr);

int		ft_print_error(char *message);
int		ft_is_numeric(char *str);
int		ft_is_op(char *str);
int		ft_atoi(char *str);

#endif
