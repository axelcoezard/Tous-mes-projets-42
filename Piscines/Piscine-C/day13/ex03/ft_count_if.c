/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:18:04 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/21 15:23:30 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_count_if(char **tab, int length, int (*f)(char*))
{
	int		count;

	count = 0;
	while (length > 0)
	{
		if (f(tab[length - 1]) != 0)
			count++;
		length--;
	}
	return (count);
}
