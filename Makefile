# Program name
NAME = cub3D

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Check OS for MLX flags
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    MLX_FLAGS = -framework OpenGL -framework AppKit
    MLX_PATH = -L/usr/local/lib
    MLX_LIB = -lmlx
else
    MLX_FLAGS =
    MLX_PATH =
    MLX_LIB =
endif

INCLUDES = -I./includes -I./libraries/libft

# Source files with new directory structure
SRCS = src/main.c \
	src/parsing/map/map_validation.c \
	src/parsing/map/map_char_validation.c \
	src/parsing/map/map_copy_utils.c \
	src/parsing/map/map_copy_utils2.c \
	src/parsing/file/file_utils.c \
	src/parsing/texture/path_rgb_utils.c \
	src/parsing/texture/texture_color_utils1.c \
	src/parsing/texture/texture_color_utils2.c \
	src/parsing/texture/texture_color_utils3.c \
	src/parsing/wall/wall_check1.c \
	src/parsing/wall/wall_check2.c \
	src/parsing/wall/wall_check3.c \
	src/parsing/utils/error_utils.c \
	src/parsing/utils/debug_utils.c \
	src/parsing/utils/init_cleanup.c \
	src/parsing/utils/parsing_utils.c

# Object files in obj directory
OBJS = $(SRCS:src/%.c=obj/%.o)

# Libraries
LIBFT = libraries/libft/libft.a

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Library paths
MLX_INC = -I/usr/local/include

# Main rule
all: $(NAME)

# Compile program
$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME) $(MLX_PATH) $(MLX_LIB)
	@echo "$(GREEN)✓ $(NAME) created$(RESET)"

$(LIBFT):
	@make -sC libraries/libft

# Compile object files
obj/%.o: src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) $(MLX_INC) -c $< -o $@
	@#echo "\033[33mCompiling: $<\033[0m"

# Clean object files
clean:
	@make -sC libraries/libft clean
	@rm -rf obj
	@echo "$(RED)✓ Objects removed$(RESET)"

# Clean everything
fclean: clean
	@make -sC libraries/libft fclean
	@rm -f $(NAME)
	@echo "$(RED)✓ $(NAME) removed$(RESET)"

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re 