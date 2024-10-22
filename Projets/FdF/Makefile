# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 14:02:21 by acoezard          #+#    #+#              #
#    Updated: 2021/11/08 12:54:50 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	fdf

OBJECTS			:=	./bin
INCLUDES		:=	./includes

LIBFT			:=	./libft

SRCS			:=	fdf.c \
					ft_draw.c \
					ft_window.c \
					ft_controllers.c \
					ft_hooks.c \
					ft_projection.c \
					ft_camera.c \
					ft_map.c \
					ft_parser.c

B_SRCS			:=	fdf_bonus.c \
					ft_draw_bonus.c \
					ft_window_bonus.c \
					ft_controllers_bonus.c \
					ft_hooks_bonus.c \
					ft_projection_bonus.c \
					ft_camera_bonus.c \
					ft_map_bonus.c \
					ft_parser_bonus.c

ifndef BONUS
SOURCES			:=	./sources
OBJS			:=	$(addprefix ${OBJECTS}/, $(SRCS:.c=.o))
else
SOURCES		:=	./sources_bonus
OBJS			:=	$(addprefix ${OBJECTS}/, $(B_SRCS:.c=.o))
endif

CC				:=	gcc
CFLAGS			:=	-Wall -Wextra -Werror -g
CINCLUDES		:=	-I ${INCLUDES}
CDEPENDENCIES	:=	-L ${LIBFT} -lft -lm -lmlx -framework OpenGL -framework AppKit

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

bonus:
	@make BONUS=1 ${NAME}

${NAME}: ${OBJS}
	@make -C ${LIBFT}
	@echo $(GREEN)"● Compilation de ${NAME}..."$(EOC)
	@${CC} ${CFLAGS} -o ${NAME} ${CDEPENDENCIES} ${OBJS}

clean:
	@echo ${GREEN}"● Supression des fichiers binaires (.o)..."$(EOC)
	@make -C ${LIBFT} clean
	@rm -rf ${OBJECTS}

fclean: clean
	@echo ${GREEN}"● Supression des executables et librairies..."$(EOC)
	@make -C ${LIBFT} fclean
	@rm -f ${NAME}

re: fclean all

.PHONY:	all bonus clean fclean re
