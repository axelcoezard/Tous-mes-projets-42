/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 09:05:28 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/26 23:22:00 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_rush.h"

int	ft_parse_input(void)
{
	char		buffer[4096];
	t_bignum	i;

	while (read(STDIN_FILENO, &buffer, 4096) != 0)
	{
		if (!ft_is_numeric(buffer))
		{
			ft_print_error(FT_ERROR);
			continue ;
		}
		if (ft_strlen(buffer))
		{
			ft_print_error(FT_ERROR);
			continue ;
		}
		i = ft_atoi(buffer);
		if (i < 0)
			ft_print_error(FT_ERROR);
		else
			ft_parse_file("numbers_en.dict", i);
	}
	return (0);
}

void	ft_parse_number(t_entry **entries, t_ubignum n)
{
	t_entry		*divider;
	int			a;

	while (n > 0)
	{
		divider = get_entry_first_dividing(entries, n);
		a = n / divider->n;
		if (n >= 100 && a == 1)
			ft_putstr(get_entry_by_n(entries, 1)->str), ft_putchar(' ');
		else if (a > 1)
			ft_parse_number(entries, a);
		ft_putstr(divider->str);
		if (n % 10 > 0 && divider->n >= 20 && divider->n < 100)
			ft_putstr("-");
		else
			ft_putchar(' ');
		n %= divider->n;
	}
}

int	ft_parse_file(char *filepath, t_ubignum number)
{
	char	**lines;
	t_entry	**entries;

	lines = get_file_lines(filepath);
	if (lines == NULL)
		return (0);
	entries = split_dict_entry(lines);
	if (number == 0)
		ft_putstr("zero");
	else
		ft_parse_number(entries, number);
	ft_putchar('\n');
	return (free_dict_entries(entries));
}
