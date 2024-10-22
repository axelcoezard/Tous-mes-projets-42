/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:16:06 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/13 20:23:09 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* ************************* INCLUDES ************************* */
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

/* ************************ STRUCTURES ************************ */
typedef struct s_node
{
	void			*content;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_list
{
	struct s_node	*first;
	struct s_node	*last;
	unsigned int	size;
}	t_list;

/* ************************ CHARACTERS ************************ */
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_islower(int c);
int			ft_isupper(int c);
int			ft_isspace(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);

/* ********************** INPUT / OUTPUT ********************** */
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putunbr_fd(unsigned int nbr, int fd);
void		ft_putunbr_base_fd(unsigned long nbr, char *base, int fd);

int			ft_printf(const char *format, ...);
int			ft_printf_char(va_list params, char flag);
int			ft_printf_string(va_list params, char flag);
int			ft_printf_ptr(va_list params, char flag);
int			ft_printf_decimal(va_list params, char flag);
int			ft_printf_integer(va_list params, char flag);
int			ft_printf_udecimal(va_list params, char flag);
int			ft_printf_hex(va_list params, char flag);
int			ft_printf_percent(va_list params, char flag);

char		*get_next_line(int fd);

/* ************************** STRINGS ************************* */
size_t		ft_strlen(const char *s);
char		*ft_strcpy(char *dest, const char *src);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
char		*ft_strcat(char *dest, const char *src);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *str, const char *to_find, size_t len);
char		*ft_strdup(const char *s);
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strtrim(const char *s1, const char *set);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		**ft_split(const char *s, char c);

/* ************************** INTEGERS ************************ */
char		*ft_itoa(int n);
int			ft_atoi(const char *pnbr);

/* ************************** MEMORY ************************** */
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memccpy(void *dest, const void *src, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);

/* *********************** LINKED LISTS *********************** */
t_list		*list_create(void);
t_node		*list_create_node(void *content);
void		list_add_front(t_list *list, void *content);
void		list_add_back(t_list *list, void *content);
void		list_remove(t_list *list, t_node *node, void (*del)(void*));
void		list_clear(t_list *list, void (*del)(void*));

#endif
