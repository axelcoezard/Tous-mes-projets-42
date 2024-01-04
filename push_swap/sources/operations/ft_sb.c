/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:17:26 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/14 20:54:29 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	ft_sb(t_stack *stack)
{
	t_list	*b;
	int		tmp;

	b = stack->b;
	tmp = *((int *) b->first->next->content);
	*((int *) b->first->next->content) = *((int *) b->first->content);
	*((int *) b->first->content) = tmp;
	ft_putstr_fd("sb\n", 1);
}
