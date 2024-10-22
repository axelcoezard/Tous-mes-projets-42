/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_add_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:31:13 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/01 11:23:25 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_list_add_front(t_list **alst, void *content)
{
	t_list	*new;

	if (alst != NULL)
	{
		new = ft_list_create(content);
		new->next = *alst;
		*alst = new;
	}
}
