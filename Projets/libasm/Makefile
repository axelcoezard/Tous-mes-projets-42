# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/26 23:44:28 by acoezard          #+#    #+#              #
#    Updated: 2022/06/20 11:48:42 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	libasm.a

# -----------------------------------------------------------------------------
# COMPILATION
# -----------------------------------------------------------------------------
SRCS	:=	ft_write.s \
			ft_read.s \
			ft_strlen.s \
			ft_strcpy.s \
			ft_strcmp.s \
			ft_strdup.s

OBJS	:=	${addprefix bin/, ${SRCS:.s=.o}}

ASM		:=	nasm
CC		:=	clang

OS = $(shell uname -s)
ifeq ($(OS), Linux)
ASM_FLAGS	:= -f elf64
else
ASM_FLAGS	:= -f macho64
endif

# -----------------------------------------------------------------------------
# COLORS
# -----------------------------------------------------------------------------
__RED		:=	"\033[1;31m"
__GREEN		:=	"\033[1;32m"
__YELLOW	:=	"\033[1;33m"
__BLUE		:=	"\033[1;36m"
__WHITE		:=	"\033[1;37m"
__EOC		:=	"\033[0;0m"

# -----------------------------------------------------------------------------
# RULES
# -----------------------------------------------------------------------------
bin/%.o: srcs/%.s
	@mkdir -p ${dir $@}
	@${ASM} ${ASM_FLAGS} $? -o $@
	@echo ${__GREEN}"Compiling "${__WHITE}$?${__EOC}

all: ${NAME}

${NAME}: ${OBJS}
	@ar rcs ${NAME} ${OBJS}
	@${CC} -o tests/tester tests/tester.c ${NAME}
	@echo ${__GREEN}"Finished "${__WHITE}${NAME}" library target"${__EOC}

clean:
	@rm -rf bin/

fclean: clean
	@rm -rf ${NAME} a.out tests/tester
	@echo ${__BLUE}"Cleaned "${__WHITE}"bin target(s)"${__EOC}

re: fclean all

.PHONY: all clean fclean re
