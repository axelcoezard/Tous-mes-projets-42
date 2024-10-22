/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_strs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:31:09 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/22 13:15:47 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_list_push_strs(int size, char **strs)
{
	t_list	*begin_list;
	t_list	*node;
	int		i;

	begin_list = ft_create_elem(strs[0]);
	i = size - 1;
	node = begin_list;
	while (i > 0)
	{
		node->next = ft_create_elem(strs[i]);
		node = node->next;
		i--;
	}
	return (begin_list);
}
