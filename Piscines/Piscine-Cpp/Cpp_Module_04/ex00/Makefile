# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 10:19:39 by acoezard          #+#    #+#              #
#    Updated: 2021/12/14 11:14:30 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	animal

SOURCES			:=	./sources
INCLUDES		:=	./includes
OBJECTS			:=	bin

SRCS			:=	main.cpp \
					Animal.cpp \
					Cat.cpp \
					Dog.cpp \
					WrongAnimal.cpp \
					WrongCat.cpp

OBJS			:=	$(addprefix ${OBJECTS}/, $(SRCS:.cpp=.o))

CC				:=	clang++
CFLAGS			:=	-Wall -Wextra -Werror
CINCLUDES		:=	-I ${INCLUDES}

GREEN			:=	"\033[1;32m"
BLUE			:=	"\033[1;36m"
EOC				:=	"\033[0m"

${OBJECTS}/%.o: ${SOURCES}/%.cpp
	@mkdir -p $(dir $@)
	@echo "● Compilation de "${BLUE}"${notdir $<}"${EOC}"."
	@${CC} ${CFLAGS} -o $@ -c $< ${CINCLUDES}

all: ${NAME}

${NAME}: ${OBJS}
	@echo $(GREEN)"● Compilation de ${NAME}..."$(EOC)
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS}

clean:
	@echo $(GREEN)"● Suppression des fichiers binaires (.o)..."$(EOC)
	@rm -rf ${OBJECTS}

fclean: clean
	@echo ${GREEN}"● Supression des executables et librairies..."$(EOC)
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
