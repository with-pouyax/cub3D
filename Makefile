# === Compiler and Flags ===
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -MMD -MP

# === Executable Name ===
NAME    = cub3D

# === Directories ===
SRC_DIR     = src
OBJ_DIR     = obj
INCLUDE_DIR = includes
LIBFT_DIR   = libraries/libft

# === MLX Flags ===
MLX_FLAGS   = -lmlx -lXext -lX11 -lm

# === Terminal Colors ===
GREEN   = \033[0;32m
YELLOW  = \033[1;33m
BLUE    = \033[1;34m
CYAN    = \033[0;36m
RED     = \033[0;31m
RESET   = \033[0m

# === Source Files ===
SRC = \
	src/main.c \
	src/test_mlx.c \
	src/drawings/drawings.c \
	src/drawings/mini_map.c \
	src/drawings/draw_minimap.c \
	src/drawings/recasting1.c \
	src/drawings/recasting2.c \
	src/mlx/mlx_init.c \
	src/mlx/mlx_events.c \
	src/mlx/draw.c \
	src/mlx/event_hooks.c \
	src/mlx/player_movements1.c \
	src/mlx/player_movements2.c \
	src/mlx/movement_functions.c \
	src/mlx/start_game.c \
	src/parsing/map/map_validation.c \
	src/parsing/map/map_char_validation2.c \
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
	src/parsing/utils/clean_1.c \
	src/parsing/utils/clean_2.c \
	src/parsing/utils/parsing_utils.c \
	src/parsing/utils/parsing_utils2.c

# === Object and Dependency Files ===
OBJ = $(SRC:.c=.o)
OBJ := $(OBJ:$(SRC_DIR)/%=$(OBJ_DIR)/%)
DEP = $(OBJ:.o=.d)

# === Build All ===
all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(CYAN)🔧 [Step 1] Building libft...$(RESET)"
	@make -C $(LIBFT_DIR) --silent
	@echo "$(CYAN)🎨 [Step 2] Linking cub3D...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)✅ Done: $(NAME) built successfully.$(RESET)"

# === Compile Each .c to .o and .d ===
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -c $< -o $@

# === Clean Object and Dependency Files ===
clean:
	@echo "$(RED)🧹 Cleaning object and dependency files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean --silent

# === Clean Everything ===
fclean: clean
	@echo "$(RED)🧨 Removing executable...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --silent

# === Rebuild Everything ===
re: fclean all

# === Include Dependency Files if They Exist ===
-include $(DEP)

# === Declare Phony Targets ===
.PHONY: all clean fclean re
