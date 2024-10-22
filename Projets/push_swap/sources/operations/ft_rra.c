/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rra.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:12:01 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/14 23:42:53 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	ft_rra(t_stack *stack)
{
	t_node	*node;
	int		*tmp;

	tmp = malloc(sizeof(int));
	*tmp = *((int *) stack->a->last->content);
	node = stack->a->last->prev;
	node->next = NULL;
	stack->a->last = node;
	list_add_front(stack->a, tmp);
	ft_putstr_fd("rra\n", 1);
}
