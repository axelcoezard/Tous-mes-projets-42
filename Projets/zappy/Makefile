# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 14:26:55 by acoezard          #+#    #+#              #
#    Updated: 2024/04/16 11:17:34 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	mkdir -p build
	cd build; cmake ..; make -j4
	cp -f build/client .
	cp -f build/server .
	cp -f build/gfx .

fclean:
	rm -rf build
	rm -f client
	rm -f server
	rm -f gfx

re: fclean all
