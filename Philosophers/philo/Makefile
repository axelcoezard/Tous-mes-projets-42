# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/16 13:31:11 by acoezard          #+#    #+#              #
#    Updated: 2021/11/25 18:58:09 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	philo

SOURCES			:=	./sources
INCLUDES		:=	./includes
OBJECTS			:=	./bin

SRCS			:=	main.c \
					ft_libft.c \
					ft_check.c \
					ft_parse.c \
					ft_time.c \
					ft_print.c \
					ft_philo.c \
					ft_philo_actions.c \
					ft_threads.c

OBJS			:=	$(addprefix ${OBJECTS}/, $(SRCS:.c=.o))

CC				:=	clang
CFLAGS			:=	-Wall -Wextra -Werror #-g #-fsanitize=address
CINCLUDES		:=	-I ${INCLUDES}
CDEPENDENCIES	:=	-pthread -lpthread

BLACK			:=	"\033[1;30m"
RED				:=	"\033[1;31m"
GREEN			:=	"\033[1;32m"
CYAN			:=	"\033[1;35m"
BLUE			:=	"\033[1;36m"
WHITE			:=	"\033[1;37m"
EOC				:=	"\033[0;0m"

${OBJECTS}/%.o: ${SOURCES}/%.c
	@mkdir -p $(dir $@)
	@echo "● Compilation de "$(BLUE)"${notdir $<}"$(EOC)"."
	@${CC} ${CFLAGS} -o $@ -c $< ${CINCLUDES}

all: ${NAME}

${NAME}: ${OBJS}
	@echo $(GREEN)"● Compilation de ${NAME}..."$(EOC)
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${CDEPENDENCIES}

clean:
	@echo ${GREEN}"● Supression des fichiers binaires (.o)..."$(EOC)
	@rm -rf ${OBJECTS}

fclean: clean
	@echo ${GREEN}"● Supression des executables et librairies..."$(EOC)
	@rm -f ${NAME}

re: fclean all

.PHONY:	all clean fclean re
