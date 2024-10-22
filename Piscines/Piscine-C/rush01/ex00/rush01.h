/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 09:17:25 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/19 23:17:56 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH01_H
# define RUSH01_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_tab {
	int		*grid;
	int		size;
}				t_tab;

typedef struct s_params {
	int		*a;
	int		*dir;
}				t_params;

int		ft_print_error(void);

void	ft_putchar(char c);

void	ft_putstr(char *str);

void	ft_putnbr(int nbr);

void	ft_swap(int *a, int *b);

int		ft_factorial(int n);

int		*ft_split(char *str);

int		ft_atoi(char *str);

t_tab	*ft_create_tab(int size);

void	ft_print_tab(t_tab *tab);

void	ft_set_tab(t_tab *tab, int x, int y, int height);

int		ft_get_tab(t_tab *tab, int x, int y);

int		ft_check_tab(t_tab *tab);

void	ft_destroy_tab(t_tab *tab);

int		ft_solve(t_tab *tab, int *input);

int		ft_backtrack(void);

int		*ft_johnson(t_params *params, int n);

int		**ft_trotter(int n, int *contraints);

int		*ft_horizontal_check(int *row, int *contraints, int n);

int		*ft_vertical_check(int *row, int *contraints, int n);

#endif
