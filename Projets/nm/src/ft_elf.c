/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:23:00 by acoezard          #+#    #+#             */
/*   Updated: 2024/10/15 14:16:46 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int ft_elf_open(t_elf_file* file)
{
	file->fd = open(file->name, O_RDONLY);

	if (file->fd < 0)
		return EXIT_FAILURE;

	struct stat st;
	if (fstat(file->fd, &st) < 0)
	{
		close(file->fd);
		return EXIT_FAILURE;
	}

	file->size = st.st_size;
	file->ptr = mmap(NULL, file->size, PROT_READ, MAP_PRIVATE, file->fd, 0);

	if (file->ptr == MAP_FAILED || file->ptr == NULL)
	{
		close(file->fd);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int ft_elf_check_architecture(t_elf_file* file)
{
	const Elf64_Ehdr* header = (Elf64_Ehdr*) file->ptr;

	if (header->e_ident[EI_MAG0] != ELFMAG0 || header->e_ident[EI_MAG1] != ELFMAG1 ||
		header->e_ident[EI_MAG2] != ELFMAG2 || header->e_ident[EI_MAG3] != ELFMAG3 ) {
		return EXIT_FAILURE;
	}

	if (header->e_ident[EI_CLASS] == ELFCLASS64)		file->arch = ARCH_X64;
	else if (header->e_ident[EI_CLASS] == ELFCLASS32)	file->arch = ARCH_X86_32;
	else												file->arch = ARCH_UNKNOWN;

	return EXIT_SUCCESS;
}

int ft_elf_close(const t_elf_file* file)
{
	if (file->ptr != NULL)	munmap(file->ptr, file->size);
	if (file->fd >= 0)		close(file->fd);
	return EXIT_SUCCESS;
}