/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:11:49 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/22 12:15:20 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

int	ft_list_size(t_list *begin_list)
{
	t_list	*current;
	int		count;

	current = begin_list;
	count = 1;
	while (current->next != NULL)
	{
		current = current->next;
		count++;
	}
	return (count);
}
