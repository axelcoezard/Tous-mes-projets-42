# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/24 21:19:06 by acoezard          #+#    #+#              #
#    Updated: 2021/10/29 14:02:22 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES		:=	./sources
OBJECTS		:=	./bin
INCLUDES	:=	./includes

SRCS		:=	ft_putchar_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_atoi.c \
				ft_isdigit.c \
				ft_isspace.c \
				ft_strlen.c

OBJS		:=	$(addprefix ${OBJECTS}/, $(SRCS:.c=.o))

CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror
CINCLUDES	:=	-I ${INCLUDES}

BLACK		:=	"\033[1;30m"
RED			:=	"\033[1;31m"
GREEN		:=	"\033[1;32m"
CYAN		:=	"\033[1;35m"
BLUE		:=	"\033[1;36m"
WHITE		:=	"\033[1;37m"
EOC			:=	"\033[0;0m"

${OBJECTS}/%.o: ${SOURCES}/%.c
	@mkdir -p $(dir $@)
	@echo "● Compilation de "$(BLUE)"${notdir $<}"$(EOC)"."
	@${CC} ${CFLAGS} -o $@ -c $< ${CINCLUDES}

all: server client

server: ${OBJS} ${OBJECTS}/server.o
	@echo $(GREEN)"● Compilation du server..."$(EOC)
	@${CC} ${CFLAGS} ${CINCLUDES} -o server ${OBJS} ${OBJECTS}/server.o

client: ${OBJS} ${OBJECTS}/client.o
	@echo $(GREEN)"● Compilation du client..."$(EOC)
	@${CC} ${CFLAGS} ${CINCLUDES} -o client ${OBJS} ${OBJECTS}/client.o

bonus: server_bonus client_bonus

server_bonus: ${OBJS} ${OBJECTS}/server_bonus.o
	@echo $(GREEN)"● Compilation du server (bonus)..."$(EOC)
	@${CC} ${CFLAGS} ${CINCLUDES} -o server ${OBJS} ${OBJECTS}/server_bonus.o

client_bonus: ${OBJS} ${OBJECTS}/client_bonus.o
	@echo $(GREEN)"● Compilation du client (bonus)..."$(EOC)
	@${CC} ${CFLAGS} ${CINCLUDES} -o client ${OBJS} ${OBJECTS}/client_bonus.o

clean:
	@echo ${GREEN}"● Supression des fichiers binaires (.o)..."$(EOC)
	@rm -rf ${OBJECTS}

fclean: clean
	@echo ${GREEN}"● Supression des executables et librairies..."$(EOC)
	@rm -rf server client

re: fclean all

.PHONY: all bonus clean fclean re
