# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/16 17:42:54 by acoezard          #+#    #+#              #
#    Updated: 2021/09/20 12:01:11 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ./srcs/ft_putchar.c \
	   ./srcs/ft_putstr.c \
	   ./srcs/ft_strcmp.c \
	   ./srcs/ft_strlen.c \
	   ./srcs/ft_swap.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c -I includes $< -o ${<:.c=.o} 

${NAME}: ${OBJS}
	ar rc ${NAME} ${OBJS}
	ranlib ${NAME}	

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
