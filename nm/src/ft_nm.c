/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:56:41 by acoezard          #+#    #+#             */
/*   Updated: 2024/10/22 11:31:00 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int ft_nm(t_elf_file* file, int fileCount)
{
	if (ft_elf_open(file) > 0)
	{
		ft_print_nm_error(file, "No such file", 1);
		return EXIT_FAILURE;
	}

	if (ft_elf_check_architecture(file) == EXIT_FAILURE || file->arch == ARCH_UNKNOWN)
	{
		ft_print_nm_error(file, "file format not recognized", 0);
		ft_elf_close(file);
		return EXIT_FAILURE;
	}

	if (fileCount > 1)
		ft_print_filename(file->name);

	size_t symbolsCount = 0;
	if (file->arch == ARCH_X86_32)	symbolsCount = ft_nm_x86_32(file);
	if (file->arch == ARCH_X64)		symbolsCount = ft_nm_x64(file);

	if (symbolsCount == 0)
		ft_print_nm_error(file, "no symbols", 1);

	return ft_elf_close(file);
}
