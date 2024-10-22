# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/24 18:23:16 by acoezard          #+#    #+#              #
#    Updated: 2021/09/26 22:25:28 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rush-02

SRCS = ./srcs/main.c \
	   ./srcs/ft_rush.c \
	   ./srcs/ft_print.c \
	   ./srcs/ft_atoi.c \
	   ./srcs/ft_split.c \
	   ./srcs/ft_dict.c \
	   ./srcs/ft_entry.c \
	   ./srcs/ft_file.c \
	   ./srcs/ft_parser.c \
	   ./srcs/ft_check_args.c \
	   ./srcs/ft_string.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

${NAME}:
	${CC} ${CFLAGS} -I includes -o ${NAME} ${SRCS} 

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
