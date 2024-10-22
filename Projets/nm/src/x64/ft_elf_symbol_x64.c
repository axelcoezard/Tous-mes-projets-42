/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elf_symbol_x64.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:56:41 by acoezard          #+#    #+#             */
/*   Updated: 2024/10/15 14:17:04 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

// Inspired by https://stackoverflow.com/questions/15225346/how-to-display-the-symbols-type-like-the-nm-command
unsigned char ft_elf_symbol_x64(const Elf64_Sym* symtab, const Elf64_Ehdr* ehdr, const Elf64_Shdr* shdr)
{
	Elf32_Word section_type = shdr[symtab->st_shndx].sh_type;
	Elf32_Word section_flags = shdr[symtab->st_shndx].sh_flags;
	const unsigned char symbol_bind = ELF32_ST_BIND(symtab->st_info);
	const unsigned char symbol_type = ELF32_ST_TYPE(symtab->st_info);

	char symbol = '?';

	if (symbol_bind == STB_GNU_UNIQUE)
		symbol ='u';
	else if(symbol_type == STT_GNU_IFUNC)
		symbol ='i';
	else if (symbol_bind == STB_WEAK && symbol_type == STT_OBJECT)
	{
		symbol ='V';
		if (symtab->st_shndx == SHN_UNDEF)
			symbol ='v';
	}
	else if (symbol_bind == STB_WEAK && symbol_type != STT_OBJECT)
	{
		symbol ='W';
		if (symtab->st_shndx == SHN_UNDEF)
			symbol ='w';
	}
	else if (symbol_bind == STB_WEAK)
	{
		symbol ='W';
		if (symtab->st_shndx == SHN_UNDEF)
			symbol ='w';
	}
	else if (symtab->st_shndx == SHN_UNDEF)
		symbol ='U';
	else if (symtab->st_shndx == SHN_ABS)
		symbol ='A';
	else if (symtab->st_shndx == SHN_COMMON)
		symbol ='C';
	else if (symtab->st_shndx < ehdr->e_shnum)
	{
		symbol ='D';

		if (section_type == SHT_NOBITS)
			symbol ='B';
		else if (!(section_flags & SHF_WRITE))
		{
			symbol ='R';
			if(section_flags & SHF_ALLOC && section_flags & SHF_EXECINSTR)
				symbol ='T';
		}
		else if(section_flags & SHF_EXECINSTR)
			symbol ='T';
	}

	if (symbol_bind == STB_LOCAL && symbol != '?')
		symbol += 32;

	return symbol;
}