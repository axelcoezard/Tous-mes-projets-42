/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 17:02:12 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/21 15:24:27 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_op(char *str)
{
	int		size;
	char	*operators;

	size = 0;
	while (str[size])
		size++;
	if (size != 1)
		return (0);
	operators = "+-/*%";
	while (*operators)
	{
		if (str[0] == *operators)
			return (1);
		operators++;
	}
	return (0);
}
