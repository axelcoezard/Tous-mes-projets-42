/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 10:59:54 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/22 11:46:05 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H

# include <unistd.h>
# include <stdlib.h>

typedef struct	s_list
{
	struct s_list	*next;
	void			*data;
}				t_list;

t_list	*ft_create_elem(void *data);

void	ft_list_push_front(t_list **begin_list, void *data);

int		ft_list_size(t_list *begin_list);

t_list	*ft_list_last(t_list *begin_list);

void	ft_list_push_back(t_list **begin_list, void *data);

#endif
