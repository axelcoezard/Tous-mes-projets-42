/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ss.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:19:21 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/14 20:55:24 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	ft_ss(t_stack *stack)
{
	t_list	*a;
	t_list	*b;
	int		tmpa;
	int		tmpb;

	a = stack->a;
	b = stack->b;
	tmpa = *((int *) a->first->next->content);
	tmpb = *((int *) b->first->next->content);
	*((int *) a->first->next->content) = *((int *) a->first->content);
	*((int *) b->first->next->content) = *((int *) b->first->content);
	*((int *) a->first->content) = tmpa;
	*((int *) b->first->content) = tmpb;
	ft_putstr_fd("ss\n", 1);
}
