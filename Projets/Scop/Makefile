NAME			:=	scop

SOURCES			:=	srcs
INCLUDES		:=	includes
OBJECTS			:=	bin

#define generate_sources =
#	find * -name *.cpp -type f -print | while IFS= read -r -d $'\n' file; do echo ${file#*/}; done
#endef
#SRCS			:=	$(value generate_sources)

SRCS			:=	${shell bash ./generate_sources.sh}
OBJS			:=	$(addprefix $(OBJECTS)/, $(SRCS:.cpp=.o))

GLFW			:=	./libs/GLFW
GLEW			:=	./libs/GLEW
STD				:=	./libs/STB

CC				:=	clang++
CFLAGS			:=	-std=c++11 -Wall -Wextra #-Wno-deprecated-declarations #-fsanitize=address

CINCLUDES		:=  -I${GLFW}/include/ \
					-I${GLEW}/include/ \
					-I${STB}/include/ \
					${shell bash ./generate_includes.sh}

OS = $(shell uname -s)

ifeq ($(OS), Linux)
	CDEPENDENCIES	:=	-L$(GLFW)/lib/linux -lglfw -lrt -lm -ldl \
						-L$(GLEW)/lib/linux -L/usr/lib64 -lGLEW -lGL -lX11 -lGLU -lOpenGL
else
	CDEPENDENCIES	:=	-L$(GLFW)/lib/macos -lglfw -lm \
						-L$(GLEW)/lib/macos -lGLEW \
						-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
endif

BLACK			:=	"\033[1;30m"
RED				:=	"\033[1;31m"
GREEN			:=	"\033[1;32m"
CYAN			:=	"\033[1;35m"
BLUE			:=	"\033[1;36m"
WHITE			:=	"\033[1;37m"
EOC				:=	"\033[0;0m"

${OBJECTS}/%.o: ${SOURCES}/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compilation de "$(BLUE)"${notdir $<}"$(EOC)"."
	@${CC} ${CFLAGS} -o $@ -c $< ${CINCLUDES}

all: ${NAME}

${NAME}: ${OBJS}
	@echo $(GREEN)"Compilation de ${NAME} ..."$(EOC)
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${CDEPENDENCIES}

run:
	@./${NAME}

clean:
	@echo ${RED}"Supression des objets .o ..."$(EOC)
	@rm -rf ${OBJECTS}

fclean: clean
	@echo ${RED}"Supression de l'executables ..."$(EOC)
	@rm ${NAME}

re: fclean all

.PHONY:	all clean fclean re
