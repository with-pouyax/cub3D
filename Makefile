

# Program name
NAME = cub3d

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I. -I./libraries/libft

# Source files
SRCS = main.c check_walls.c
OBJS = $(SRCS:.c=.o)

# Libraries
LIBFT = libraries/libft/libft.a

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Main rule
all: $(NAME)

# Compile program
$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created$(RESET)"

$(LIBFT):
	@make -sC libraries/libft

# Compile object files
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	@make -sC libraries/libft clean
	@rm -f $(OBJS)
	@echo "$(RED)✓ Objects removed$(RESET)"

# Clean everything
fclean: clean
	@make -sC libraries/libft fclean
	@rm -f $(NAME)
	@echo "$(RED)✓ $(NAME) removed$(RESET)"

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re 