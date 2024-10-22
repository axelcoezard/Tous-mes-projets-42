# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/20 14:43:06 by acoezard          #+#    #+#              #
#    Updated: 2021/09/21 15:30:44 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = do-op

SRCS = ./srcs/do_op.c \
	   ./srcs/ft_putchar.c \
	   ./srcs/ft_putstr.c \
	   ./srcs/ft_putnbr.c \
	   ./srcs/ft_is_numeric.c \
	   ./srcs/ft_is_op.c \
	   ./srcs/ft_atoi.c

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

