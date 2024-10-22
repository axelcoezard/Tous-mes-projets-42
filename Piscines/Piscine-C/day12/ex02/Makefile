# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/20 14:43:06 by acoezard          #+#    #+#              #
#    Updated: 2021/09/27 17:53:18 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_tail

SRCS = ./srcs/ft_tail.c \
	   ./srcs/ft_string.c \
	   ./srcs/ft_is_numeric.c \
	   ./srcs/ft_atoi.c \
	   ./srcs/ft_print_error.c \
	   ./srcs/ft_print.c

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
