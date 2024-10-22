# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/30 13:03:10 by acoezard          #+#    #+#              #
#    Updated: 2021/12/09 10:59:11 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	horde

SOURCES			:=	./sources
INCLUDES		:=	./includes
OBJECTS			:=	./bin

SRCS			:=	main.cpp \
					Zombie.cpp \
					ZombieHorde.cpp

OBJS			:=	$(addprefix ${OBJECTS}/, $(SRCS:.cpp=.o))

CC				:=	clang++
CFLAGS			:=	-Wall -Wextra -Werror
CINCLUDES		:=	-I ${INCLUDES}

GREEN			:=	"\033[1;32m"
BLUE			:=	"\033[1;36m"
EOC				:=	"\033[0;0m"

${OBJECTS}/%.o: ${SOURCES}/%.cpp
	@mkdir -p $(dir $@)
	@echo "● Compilation de "$(BLUE)"${notdir $<}"$(EOC)"."
	@${CC} ${CFLAGS} -o $@ -c $< ${CINCLUDES}

all: ${NAME}

${NAME}: ${OBJS}
	@echo $(GREEN)"● Compilation de ${NAME}..."$(EOC)
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS}

clean:
	@echo ${GREEN}"● Supression des fichiers binaires (.o)..."$(EOC)
	@rm -rf ${OBJECTS}

fclean: clean
	@echo ${GREEN}"● Supression des executables et librairies..."$(EOC)
	@rm -f ${NAME}

re: fclean all

.PHONY:	all clean fclean re
