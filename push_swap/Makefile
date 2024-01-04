# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 14:02:21 by acoezard          #+#    #+#              #
#    Updated: 2021/11/14 23:45:22 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	push_swap

SOURCES			:=	./sources
INCLUDES		:=	./includes
OBJECTS			:=	./bin

LIBFT			:=	./libft

SRCS			:=	push_swap.c \
					ft_puterror.c \
					ft_tab.c \
					ft_stack.c \
					ft_check.c \
					ft_parse.c \
					ft_sort.c \
					operations/ft_pa.c \
					operations/ft_pb.c \
					operations/ft_ra.c \
					operations/ft_rb.c \
					operations/ft_rr.c \
					operations/ft_rra.c \
					operations/ft_rrb.c \
					operations/ft_rrr.c \
					operations/ft_sa.c \
					operations/ft_sb.c \
					operations/ft_ss.c

OBJS			:=	$(addprefix ${OBJECTS}/, $(SRCS:.c=.o))

CC				:=	gcc
CFLAGS			:=	-Wall -Wextra -Werror
CINCLUDES		:=	-I ${INCLUDES}
CDEPENDENCIES	:=	-L${LIBFT} -lft

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
	@make -C ${LIBFT} --no-print-directory
	@echo $(GREEN)"● Compilation de ${NAME}..."$(EOC)
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${CDEPENDENCIES}

clean:
	@echo ${GREEN}"● Supression des fichiers binaires (.o)..."$(EOC)
	@make -C ${LIBFT} clean --no-print-directory
	@rm -rf ${OBJECTS}

fclean: clean
	@echo ${GREEN}"● Supression des executables et librairies..."$(EOC)
	@make -C ${LIBFT} fclean --no-print-directory
	@rm -f ${NAME}

re: fclean all

.PHONY:	all clean fclean re
