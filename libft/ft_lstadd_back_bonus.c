/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:43:24 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/18 17:47:32 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;

	if (alst != NULL)
	{
		if (*alst == NULL)
			*alst = new;
		else
		{
			last = ft_lstlast(*alst);
			last->next = new;
		}
	}
}
