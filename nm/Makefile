NAME = ft_nm

SRC_FILES = src/main.c \
			src/ft_nm.c \
			src/x64/ft_nm_x64.c \
			src/x86_32/ft_nm_x86_32.c \
			src/ft_elf.c \
			src/ft_utils.c \
			src/ft_elf_symbol.c \
			src/x64/ft_elf_symbol_x64.c \
			src/x86_32/ft_elf_symbol_x86_32.c

OBJ_PATH = build
OBJ_FILES = $(SRC_FILES:src/%.c=$(OBJ_PATH)/%.o)

CFLAGS = -Wall -Wextra -Werror -Iinclude -O3

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_PATH)/%.o: src/%.c | $(OBJ_PATH)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

test:
	bash ./tests/test-all.bash

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re