/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:53:36 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/21 17:11:57 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/do_op.h"

int	ft_print_error(char *message)
{
	if (message == NULL)
		return (0);
	ft_putstr(message);
	ft_putchar('\n');
	return (0);
}

int	ft_calculate(int a, int b, char op)
{
	int		result;

	if (op == '+')
		result = a + b;
	if (op == '-')
		result = a - b;
	if (op == '*')
		result = a * b;
	if (op == '/')
	{
		if (b == 0)
			return (ft_print_error("Stop : division by zero"));
		result = a / b;
	}
	if (op == '%')
	{
		if (b == 0)
			return (ft_print_error("Stop : modulo by zero"));
		result = a % b;
	}
	ft_putnbr(result);
	ft_putchar('\n');
	return (0);
}

int	main(int argc, char **argv)
{
	int		a;
	int		b;

	if (argc != 4)
		return (ft_print_error(NULL));
	if (!ft_is_op(argv[2]))
		return (ft_print_error("0"));
	a = ft_atoi(argv[1]);
	b = ft_atoi(argv[3]);
	ft_calculate(a, b, argv[2][0]);
	return (0);
}
