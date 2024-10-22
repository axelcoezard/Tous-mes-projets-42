/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_x86_32.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:56:41 by acoezard          #+#    #+#             */
/*   Updated: 2024/10/15 14:16:59 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#define ELF32_PADDING 8

size_t ft_nm_x86_32(const t_elf_file* file)
{
	if (file == NULL || file->ptr == NULL) return 0;

	const Elf32_Ehdr* ehdr = (Elf32_Ehdr*) file->ptr;
	const Elf32_Shdr* shdr = (Elf32_Shdr*) ((char*) file->ptr + ehdr->e_shoff);

	t_elf_symbol* symbols = NULL;
	size_t symbolsCount = 0;

	for (unsigned long i = 0; i < ehdr->e_shnum; i++)
	{
		if (shdr[i].sh_type == SHT_SYMTAB)
		{
			Elf32_Sym* symtab = (Elf32_Sym*)((char*)file->ptr + shdr[i].sh_offset);
			const char* symstrtab = (char*)file->ptr + shdr[shdr[i].sh_link].sh_offset;
			const unsigned long sym_count = shdr[i].sh_size / sizeof(Elf32_Sym);

			symbolsCount += sym_count;

			for (unsigned long j = 0; j < sym_count; j++)
			{
				if (symtab[j].st_name == 0)
					continue;

				if (ELF32_ST_TYPE(symtab[j].st_info) == STT_FILE)
					continue;

				const unsigned long address = symtab[j].st_value;
				const unsigned char type = ft_elf_symbol_x86_32(symtab + j, ehdr, shdr);
				const char* name = symstrtab + symtab[j].st_name;

				ft_elf_symbol_insert(&symbols, address, type, name[0] == '0' ? NULL : name);
			}
		}
	}

	if (symbols == NULL || symbolsCount == 0)
		return 0;

	t_elf_symbol* current = symbols;
	while (current != NULL)
	{
		if (current->type != 'A')
			ft_print_symbol(current, ELF32_PADDING);
		current = current->next;
	}

	ft_elf_symbol_free(&symbols);

	return symbolsCount;
}