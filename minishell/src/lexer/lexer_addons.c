/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_addons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:57:47 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/29 10:18:39 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_callback(char **s, int *n, int (*token)(), void *arg)
{
	int	m;

	if (token(*s, *n, arg))
		return (-1);
	m = *n;
	while (is_operator((*s)[*n]))
		(*n)++;
	if (token(*s + m, *n - m, arg))
		return (-1);
	*s += *n;
	while (is_space(**s))
		(*s)++;
	*n = 0;
	return (0);
}

int	tokenize(char *s, int (*token)(), void *arg)
{
	int	n;
	int	m;

	n = 0;
	while (1)
	{
		if (s[n] == '"' || s[n] == '\'')
		{
			m = n;
			while (s[++n] != s[m])
				if (s[n] == '\0')
					return (err("syntax error unclosed token", s, 258));
			n++;
		}
		else if (s[n] && !is_space(s[n]) && !is_operator(s[n]))
			while (s[++n] && !is_space(s[n]) && !is_operator(s[n])
				&& s[n] != '"' && s[n] != '\'')
				;
		if (is_operator(s[n]) || is_space(s[n]) || s[n] == '\0')
			if (tokenize_callback(&s, &n, token, arg))
				return (-1);
		if (s[n] == '\0')
			return (0);
	}
}
/*
int	tokenize(char *s, int (*token)(), void *arg)
{
	int	n;
	int	m;

	while (*s)
	{
		while (is_space(*s))
			s++;
		n = 0;
		while (s[n] && !is_space(s[n]) && !is_operator(s[n]))
		{
			if (s[n] == '"' || s[n] == '\'')
			{
				m = n;
				while (s[++n] != s[m])
					if (s[n] == '\0')
						return (err("syntax error unclosed token", s, 258));
			}
			n++;
		}
		token(s, n, arg);
		m = n;
		while (is_operator(s[m]))
			m++;
		token(s + n, m - n, arg);
		s += m;
	}
	return (0);
}
*/
