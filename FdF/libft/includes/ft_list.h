/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:36:18 by acoezard          #+#    #+#             */
/*   Updated: 2021/10/23 16:38:52 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H

struct s_list
{
	void			*content;
	struct s_list	*next;
};

typedef struct s_list	t_list;

t_list	*ft_list_create(void *content);
void	ft_list_add_front(t_list **alst, void *content);
void	ft_list_add_back(t_list **alst, void *content);
int		ft_list_size(t_list *lst);
t_list	*ft_list_last(t_list *lst);
void	ft_list_remove(t_list *lst, void (*del)(void*));
void	ft_list_clear(t_list **lst, void (*del)(void*));
void	ft_list_foreach(t_list *lst, void (*f)(void *));
t_list	*ft_list_map(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
