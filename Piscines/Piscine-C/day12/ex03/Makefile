# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/20 14:43:06 by acoezard          #+#    #+#              #
#    Updated: 2021/09/23 20:44:41 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_hexdump

SRCS = ./srcs/ft_hexdump.c \
	   ./srcs/ft_putchar.c \
	   ./srcs/ft_putstr.c \
	   ./srcs/ft_print_error.c \
	   ./srcs/ft_file.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

${NAME}:
	${CC} ${CFLAGS} -I includes -o ${NAME} ${SRCS} 

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re

