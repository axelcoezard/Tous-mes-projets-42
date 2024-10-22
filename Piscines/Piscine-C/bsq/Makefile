# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/27 09:09:38 by acoezard          #+#    #+#              #
#    Updated: 2021/09/30 09:34:36 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bsq

SRCS = ./srcs/main.c \
	   ./srcs/ft_bsq.c \
	   ./srcs/ft_error.c \
	   ./srcs/ft_string.c \
	   ./srcs/ft_map/ft_map_create.c \
	   ./srcs/ft_map/ft_map_define.c \
	   ./srcs/ft_map/ft_map_destroy.c \
	   ./srcs/ft_map/ft_map_fill.c \
	   ./srcs/ft_map/ft_map_get.c \
	   ./srcs/ft_map/ft_map_set.c \
	   ./srcs/ft_map/ft_map_print.c \
	   ./srcs/ft_file.c \
	   ./srcs/ft_parser.c \
	   ./srcs/ft_read_input.c \
	   ./srcs/ft_solver.c \
	   ./srcs/ft_split.c \
	   ./srcs/ft_atoi.c \
	   ./srcs/ft_check_args.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}:
	${CC} ${CFLAGS} -I includes -o ${NAME} ${SRCS}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
