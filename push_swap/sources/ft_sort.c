/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 23:29:22 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/15 11:10:16 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	sort_3_stack(t_stack *stacks)
{
	int		first;
	int		second;
	int		third;

	first = *((int *) stacks->a->first->content);
	second = *((int *) stacks->a->first->next->content);
	third = *((int *) stacks->a->last->content);
	if (first > second && second < third && first < third)
		ft_sa(stacks);
	else if (first > second && second > third)
	{
		ft_sa(stacks);
		ft_rra(stacks);
	}
	else if (first < second && second > third && first < third)
	{
		ft_sa(stacks);
		ft_ra(stacks);
	}
	else if (first > second && second < third && first > third)
		ft_ra(stacks);
	else if (first < second && second > third && first > third)
		ft_rra(stacks);
}

static void	sort_4_or_5_stack(t_stack *stacks, int median)
{
	int		pb_count;
	t_list	*a;
	t_list	*b;

	a = stacks->a;
	b = stacks->b;
	pb_count = 0;
	while (pb_count < median)
	{
		if (*((int *) a->first->content) < median)
		{
			ft_pb(stacks);
			pb_count++;
		}
		else
			ft_ra(stacks);
	}
	sort_3_stack(stacks);
	if (median > 1)
	{
		if (*((int *) b->first->content) < *((int *) b->last->content))
			ft_sb(stacks);
		ft_pa(stacks);
	}
	ft_pa(stacks);
}

void	sort_small_stack(t_stack *stacks)
{
	int		first;
	int		last;

	first = *((int *) stacks->a->first->content);
	last = *((int *) stacks->a->last->content);
	if (stacks->a->size == 2 && first > last)
		ft_ra(stacks);
	else if (stacks->a->size == 3)
		sort_3_stack(stacks);
	else if (stacks->a->size == 4)
		sort_4_or_5_stack(stacks, 1);
	else if (stacks->a->size == 5)
		sort_4_or_5_stack(stacks, 2);
}

void	sort_big_stack(t_stack *stacks)
{
	int		size;
	int		max_bits;
	int		top;
	int		i;
	int		j;

	size = stacks->a->size;
	max_bits = 0;
	while ((size - 1) >> max_bits != 0)
		max_bits++;
	i = -1;
	while (++i < max_bits)
	{
		j = -1;
		while (++j < size)
		{
			top = *((int *) stacks->a->first->content);
			if (((top >> i) & 1) == 1)
				ft_ra(stacks);
			else
				ft_pb(stacks);
		}
		while (stacks->b->first != NULL)
			ft_pa(stacks);
	}
}
