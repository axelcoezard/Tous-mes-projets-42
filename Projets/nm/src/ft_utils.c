/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:56:41 by acoezard          #+#    #+#             */
/*   Updated: 2024/10/15 14:16:31 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <string.h>

int ft_strlen(const char* str)
{
	int i = 0;
	while (str[i] != '\0')
		i++;
	return i;
}

void ft_print(int fd, const char* msg)
{
	write(fd, msg, ft_strlen(msg));
}

void ft_print_filename(const char* filename)
{
	ft_print(1, "\n");
	ft_print(1, filename);
	ft_print(1, ":\n");
}

void ft_print_error(const char* msg)
{
	ft_print(2, msg);
}

void ft_print_nm_error(t_elf_file* file, const char* msg, int quotes)
{
	ft_print_error("ft_nm: ");

	if (quotes)
		ft_print_error("'");
	ft_print_error(file->name);
	if (quotes)
		ft_print_error("'");

	ft_print_error(": ");
	ft_print_error(msg);
	ft_print_error("\n");
}

void ft_print_symbol(t_elf_symbol* symbol, const unsigned int size)
{
	unsigned long address = symbol->address;

	if (address == 0 || symbol->type == 'U' || symbol->type == 'w')
	{
		for (unsigned int i = 0; i < size; i++)
			write(1, " ", 1);
	}
	else
	{
		char* buffer = malloc(sizeof(char) * (size + 1));
		if (buffer == NULL)
			return;

		unsigned int i = size;
		while (i-- > 0)
		{
			buffer[i] = "0123456789abcdef"[address % 16];
			address /= 16;
		}

		buffer[size] = '\0';
		write(1, buffer, size);
		free(buffer);
	}

	ft_print(1, " ");
	{
		write(1, &(symbol->type), 1);
	}
	ft_print(1, " ");
	{
		ft_print(1, symbol->name == NULL ? "(null)" : symbol->name);
	}
	ft_print(1, "\n");
}

static unsigned char ft_tolower(unsigned char c)
{
	return c >= 'A' && c <= 'Z' ? c + 32 : c;
}

int ft_strcmp_ignore_underscore(const char* a, const char* b)
{
	const unsigned char* s1_bis = (const unsigned char *) a;
	const unsigned char* s2_bis = (const unsigned char *) b;

	// ignore first underscores
	while (*s1_bis == '_') s1_bis++;
	while (*s2_bis == '_') s2_bis++;

	while (*s1_bis && *s2_bis && ft_tolower(*s1_bis) == ft_tolower(*s2_bis))
	{
		s1_bis++;
		s2_bis++;

		// ignore middle underscores
		while (*s1_bis == '_') s1_bis++;
		while (*s2_bis == '_') s2_bis++;
	}

	return ft_tolower(*s1_bis) - ft_tolower(*s2_bis);
}
