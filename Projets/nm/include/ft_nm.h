/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:56:41 by acoezard          #+#    #+#             */
/*   Updated: 2024/10/15 14:17:30 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H

// includes
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <elf.h>

// structs
typedef enum
{
	ARCH_UNKNOWN,
	ARCH_X86_32,
	ARCH_X64
} t_elf_arch;

typedef struct
{
	char* name;
	size_t size;
	int fd;
	void* ptr;
	t_elf_arch arch;
} t_elf_file;

struct s_elf_symbol {
	unsigned long address;
	unsigned char type;
	const char* name;

	struct s_elf_symbol* next;
	struct s_elf_symbol* prev;
};
typedef struct s_elf_symbol t_elf_symbol;

// utils
int ft_strlen(const char* str);
void ft_print(int fd, const char* msg);
void ft_print_filename(const char* filename);
void ft_print_error(const char* msg);
void ft_print_nm_error(t_elf_file* file, const char* msg, int quotes);
void ft_print_symbol(t_elf_symbol* symbol, unsigned int size);
int ft_strcmp_ignore_underscore(const char* a, const char* b);

// elf
int ft_elf_open(t_elf_file* file);
int ft_elf_check_architecture(t_elf_file* file);
int ft_elf_close(const t_elf_file* file);

// symbols
unsigned char ft_elf_symbol_x86_32(const Elf32_Sym* symtab, const Elf32_Ehdr* ehdr, const Elf32_Shdr* shdr);
unsigned char ft_elf_symbol_x64(const Elf64_Sym* symtab, const Elf64_Ehdr* ehdr, const Elf64_Shdr* shdr);
void ft_elf_symbol_insert(t_elf_symbol** symbols, unsigned long address, unsigned char type, const char* name);
void ft_elf_symbol_free(t_elf_symbol** symbols);

// main
int ft_nm(t_elf_file* file, int fileCount);
size_t ft_nm_x86_32(const t_elf_file* file);
size_t ft_nm_x64(const t_elf_file* file);


#endif //MAIN_H
