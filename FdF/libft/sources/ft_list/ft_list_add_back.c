/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_add_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:43:24 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/23 16:41:07 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_list_add_back(t_list **alst, void *content)
{
	t_list	*last;
	t_list	*new;

	if (alst != NULL)
	{
		new = ft_list_create(content);
		if (*alst == NULL)
			*alst = new;
		else
		{
			last = ft_list_last(*alst);
			last->next = new;
		}
	}
}
