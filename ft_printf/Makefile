# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 11:42:41 by acoezard          #+#    #+#              #
#    Updated: 2021/10/21 11:54:37 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS =	ft_printf.c ft_putunbr_base_fd.c ft_putunbr_fd.c \
		ft_display_char.c ft_display_decimal.c \
		ft_display_hex.c ft_display_integer.c ft_display_percent.c \
		ft_display_ptr.c ft_display_string.c ft_display_udecimal.c

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	$(MAKE) -C ./libft
	cp libft/libft.a $(NAME)
	ar rcs ${NAME} ${OBJS}

all: ${NAME}

clean:
	$(MAKE) clean -C ./libft
	rm -f ${OBJS}

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f ${NAME}

re:	fclean all

.PHONY: all clean fclean re
