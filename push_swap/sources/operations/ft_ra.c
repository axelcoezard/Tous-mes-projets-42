/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:58:04 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/14 20:54:38 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	ft_ra(t_stack *stack)
{
	t_node	*next;
	int		*tmp;

	tmp = malloc(sizeof(int));
	*tmp = *((int *) stack->a->first->content);
	next = stack->a->first->next;
	list_add_back(stack->a, tmp);
	list_remove(stack->a, stack->a->first, free);
	stack->a->first = next;
	ft_putstr_fd("ra\n", 1);
}
