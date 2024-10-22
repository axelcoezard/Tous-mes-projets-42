# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/01 10:39:56 by acoezard          #+#    #+#              #
#    Updated: 2023/09/05 13:52:04 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	ft_ping
VERSION	:=	1.0
ARCH	:=	x86_64

# -----------------------------------------------------------------------------
# COMPILATION
# -----------------------------------------------------------------------------
SRCS	:=	main.c utils.c parse.c \
			network/socket.c network/dns.c network/loop.c \
			libft/ft_atoi.c libft/ft_memset.c libft/ft_strcpy.c

OBJS	:=	$(addprefix bin/, $(SRCS:.c=.o))

CC		:=	clang
CFLAGS	:=	-Wall -Wextra -Werror

# -----------------------------------------------------------------------------
# COLORS
# -----------------------------------------------------------------------------
__GREEN		:=	"\033[1;32m"
__BLUE		:=	"\033[1;36m"
__WHITE		:=	"\033[1;37m"
__EOC		:=	"\033[0;0m"

# -----------------------------------------------------------------------------
# RULES
# -----------------------------------------------------------------------------
bin/%.o: src/%.c
	@mkdir -p ${dir $@}
	@${CC} ${CFLAGS} -o $@ -c $< -I include
	@echo ${__GREEN}"Compiling "${__WHITE}$<${__EOC}

all: ${NAME}

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME} -lm
	@echo ${__GREEN}"Finished "${__WHITE}${NAME}" v"${VERSION}" bin target"${__EOC}

clean:
	@rm -rf bin/

fclean: clean
	@rm -rf ${NAME}
	@echo ${__BLUE}"Cleaned "${__WHITE}"bin target(s)"${__EOC}

re: fclean all

.PHONY: all fclean clean re
