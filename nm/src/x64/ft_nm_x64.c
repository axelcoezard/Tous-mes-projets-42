/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_x64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:56:41 by acoezard          #+#    #+#             */
/*   Updated: 2024/10/15 14:17:08 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#define ELF64_PADDING 16

size_t ft_nm_x64(const t_elf_file* file)
{
	if (file == NULL || file->ptr == NULL) return 0;

	const Elf64_Ehdr* ehdr = (Elf64_Ehdr*) file->ptr;
	const Elf64_Shdr* shdr = (Elf64_Shdr*) ((char*) file->ptr + ehdr->e_shoff);

	t_elf_symbol* symbols = NULL;
	size_t symbolsCount = 0;

	for (unsigned long i = 0; i < ehdr->e_shnum; i++)
	{
		if (shdr[i].sh_type == SHT_SYMTAB)
		{
			Elf64_Sym* symtab = (Elf64_Sym*)((char*)file->ptr + shdr[i].sh_offset);
			const char* symstrtab = (char*)file->ptr + shdr[shdr[i].sh_link].sh_offset;
			const unsigned long sym_count = shdr[i].sh_size / sizeof(Elf64_Sym);

			symbolsCount += sym_count;

			for (unsigned long j = 0; j < sym_count; j++)
			{
				if (symtab[j].st_name == 0)
					continue;

				if (ELF64_ST_TYPE(symtab[j].st_info) == STT_FILE)
					continue;

				const unsigned long address = symtab[j].st_value;
				const unsigned char type = ft_elf_symbol_x64(symtab + j, ehdr, shdr);
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
			ft_print_symbol(current, ELF64_PADDING);
		current = current->next;
	}

	ft_elf_symbol_free(&symbols);

	return symbolsCount;
}