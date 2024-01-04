/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 21:24:17 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/15 11:28:05 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	parse_array(t_stack *stacks, int ac, char **av, int start)
{
	size_t	i;
	int		*tmp;

	i = start;
	while (i < (size_t) ac)
	{
		if (!check_int(av[i]))
		{
			ft_puterror();
			exit(1);
		}
		tmp = malloc(sizeof(int));
		*tmp = ft_atoi(av[i]);
		list_add_back(stacks->a, tmp);
		i++;
	}
}

static void	parse_string(t_stack *stacks, char *arg)
{
	char	**words;
	size_t	i;

	words = ft_split(arg, ' ');
	i = 0;
	while (words[i] != NULL)
		i++;
	parse_array(stacks, i, words, 0);
	i = 0;
	while (words[i] != NULL)
		free(words[i++]);
	free(words);
}

t_stack	parse_args(int ac, char **av)
{
	t_stack	stacks;

	stacks = initialize_stack();
	if (ac == 2 && !check_int(av[1]))
		parse_string(&stacks, av[1]);
	else
		parse_array(&stacks, ac, av, 1);
	return (stacks);
}
