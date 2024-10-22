/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:13:55 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/11 16:38:11 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlst;
	t_list	*nelement;

	if (!lst || !f || !del)
		return (NULL);
	nlst = NULL;
	while (lst != NULL)
	{
		nelement = ft_lstnew(f(lst->content));
		if (!nelement)
		{
			ft_lstclear(&nlst, del);
			return (NULL);
		}
		ft_lstadd_back(&nlst, nelement);
		lst = lst->next;
	}
	return (nlst);
}
