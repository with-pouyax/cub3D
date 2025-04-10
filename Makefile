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
    MLX_SYSTEM = $(shell if [ -f /usr/local/lib/libmlx.a ]; then echo 1; else echo 0; fi)
else
    MLX_FLAGS = -lXext -lX11 -lm -lbsd
    MLX_SYSTEM = $(shell if [ -f /usr/lib/libmlx.a ] || [ -f /usr/local/lib/libmlx.a ]; then echo 1; else echo 0; fi)
    ifeq ($(MLX_SYSTEM),1)
        MLX_PATH = -L/usr/lib -L/usr/local/lib
        MLX_LIB = -lmlx
    else
        MLX_PATH = -L./libraries/mlx
        MLX_LIB = -lmlx
    endif
endif

INCLUDES = -I./includes -I./libraries/libft -I./libraries/mlx

# Source files with new directory structure
SRCS = src/main.c \
	src/test_mlx.c \
	src/drawings/drawings.c \
	src/mlx/mlx_init.c \
	src/mlx/mlx_events.c \
	src/mlx/player_movements.c \
	src/mlx/movement_functions.c \
	src/mlx/movement_rotate.c \
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
	src/parsing/utils/init_player.c \
	src/parsing/utils/parsing_utils.c

# Object files in obj directory
OBJS = $(SRCS:src/%.c=obj/%.o)

# Libraries
LIBFT = libraries/libft/libft.a
MLX = libraries/mlx/libmlx.a

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Main rule
all: $(LIBFT) check_mlx $(NAME)

# Force using local MLX library for testing
test-local-mlx: clean-mlx
	@echo "$(GREEN)Forcing use of local MLX library for testing$(RESET)"
	@if [ ! -d libraries/mlx ]; then \
		echo "$(GREEN)Cloning MLX library...$(RESET)"; \
		mkdir -p libraries/mlx; \
		git clone https://github.com/42Paris/minilibx-linux.git libraries/mlx; \
		rm -rf libraries/mlx/.git; \
	fi
	@$(MAKE) -sC libraries/mlx > /dev/null 2>&1 || $(MAKE) -C libraries/mlx
	@$(MAKE) MLX_SYSTEM=0

# Clean MLX
clean-mlx:
	@if [ -d libraries/mlx ]; then \
		$(MAKE) -sC libraries/mlx clean > /dev/null 2>&1 || $(MAKE) -C libraries/mlx clean; \
	fi

# Check if MLX needs to be compiled
check_mlx:
ifeq ($(MLX_SYSTEM),0)
	@echo "$(GREEN)Using local MLX library$(RESET)"
	@if [ ! -d libraries/mlx ]; then \
		echo "$(GREEN)Cloning MLX library...$(RESET)"; \
		mkdir -p libraries/mlx; \
		git clone https://github.com/42Paris/minilibx-linux.git libraries/mlx; \
		rm -rf libraries/mlx/.git; \
	fi
	@$(MAKE) -sC libraries/mlx > /dev/null 2>&1 || $(MAKE) -C libraries/mlx
else
	@echo "$(GREEN)Using system MLX library$(RESET)"
endif

# Compile libft
$(LIBFT):
	@make -sC libraries/libft

# Compile program
$(NAME): $(LIBFT) $(OBJS)
ifeq ($(MLX_SYSTEM),0)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(MLX_PATH) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)
else
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(MLX_PATH) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)
endif
	@echo "$(GREEN)✓ $(NAME) created$(RESET)"

# Compile object files
obj/%.o: src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@#echo "\033[33mCompiling: $<\033[0m"

# Clean object files
clean:
	@make -sC libraries/libft clean
ifeq ($(MLX_SYSTEM),0)
	@if [ -d libraries/mlx ]; then \
		$(MAKE) -sC libraries/mlx clean > /dev/null 2>&1 || $(MAKE) -C libraries/mlx clean; \
	fi
endif
	@rm -rf obj
	@echo "$(RED)✓ Objects removed$(RESET)"

# Clean everything
fclean: clean
	@make -sC libraries/libft fclean
	@rm -f $(NAME)
	@echo "$(RED)✓ $(NAME) removed$(RESET)"

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re check_mlx test-local-mlx clean-mlx 