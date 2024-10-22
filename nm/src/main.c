/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:19:39 by acoezard          #+#    #+#             */
/*   Updated: 2024/10/15 14:16:21 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int main(int argc, char** argv)
{
	if (argv == NULL)
		return EXIT_FAILURE;

	if (argc < 2)
	{
		t_elf_file file;
		file.name = "a.out";

		return ft_nm(&file, 1);
	}

	int status = EXIT_SUCCESS;
	for (int i = 1; i < argc; i++)
	{
		t_elf_file file;
		file.name = argv[i];

		if (ft_nm(&file, argc - 1) > 0)
			status = EXIT_FAILURE;
	}

	return status;
}
