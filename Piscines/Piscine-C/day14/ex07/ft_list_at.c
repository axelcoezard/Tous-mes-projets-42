/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 13:54:44 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/22 14:28:50 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list *ft_list_at(t_list *begin_list, unsigned int nbr)
{
	t_list			*current;
	unsigned int	count;

	current = begin_list;
	count = 1;
	while (current->next != NULL && nbr == count)
	{
		current = current->next;
		count++;
	}
	return (current);
}
