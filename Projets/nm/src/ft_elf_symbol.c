/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elf_symbol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:56:41 by acoezard          #+#    #+#             */
/*   Updated: 2024/10/15 14:16:43 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void ft_elf_symbol_insert(t_elf_symbol** symbols, const unsigned long address, const unsigned char type, const char* name)
{
	t_elf_symbol* symbol = malloc(sizeof(t_elf_symbol));
	if (symbol == NULL)
		return;

	symbol->address = address;
	symbol->type = type;
	symbol->name = name;
	symbol->next = NULL;
	symbol->prev = NULL;

	t_elf_symbol* current = *symbols;
	t_elf_symbol* previous = NULL;

	while (current != NULL && (name == NULL || ft_strcmp_ignore_underscore(current->name, name) < 0))
		previous = current,	current = current->next;

	symbol->next = current;
	symbol->prev = previous;

	if (previous == NULL) *symbols = symbol;
	else previous->next = symbol;
	if (current != NULL) current->prev = symbol;
}

void ft_elf_symbol_free(t_elf_symbol** symbols)
{
	t_elf_symbol* current = *symbols;
	while (current != NULL)
	{
		t_elf_symbol* next = current->next;
		free(current);
		current = next;
	}
	*symbols = NULL;
}