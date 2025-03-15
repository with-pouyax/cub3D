#!/bin/bash

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}Setting up Cub3D project...${NC}"

# Check OS
OS=$(uname)
echo -e "${YELLOW}Detected OS: ${OS}${NC}"

# Install dependencies based on OS
if [ "$OS" = "Linux" ]; then
    echo -e "${YELLOW}Installing dependencies for Linux...${NC}"
    sudo apt-get update
    sudo apt-get install -y libxext-dev libxrandr-dev libx11-dev libbsd-dev libssl-dev
elif [ "$OS" = "Darwin" ]; then
    echo -e "${YELLOW}macOS detected. No additional dependencies needed.${NC}"
else
    echo -e "${RED}Unsupported OS. Please install dependencies manually.${NC}"
    exit 1
fi

# Create directories if they don't exist
echo -e "${YELLOW}Creating necessary directories...${NC}"
mkdir -p libraries
mkdir -p textures
mkdir -p maps

# Check if MLX is already cloned
if [ ! -d "libraries/mlx" ]; then
    echo -e "${YELLOW}Cloning MLX library...${NC}"
    mkdir -p libraries/mlx
    git clone https://github.com/42Paris/minilibx-linux.git libraries/mlx
    # Remove .git directory to avoid git submodule issues
    rm -rf libraries/mlx/.git
    echo -e "${GREEN}MLX library cloned successfully!${NC}"
else
    echo -e "${YELLOW}MLX library already exists. Skipping clone.${NC}"
fi

# Fix MLX library configuration
echo -e "${YELLOW}Fixing MLX library configuration...${NC}"

# Create the test directory in MLX if it doesn't exist
if [ ! -d "libraries/mlx/test" ]; then
    echo -e "${YELLOW}Creating missing test directory in MLX...${NC}"
    mkdir -p libraries/mlx/test
    echo -e "${GREEN}Test directory created successfully!${NC}"
fi

# Create a basic Makefile.mk in the test directory
echo -e "${YELLOW}Creating Makefile.mk in test directory...${NC}"
cat > libraries/mlx/test/Makefile.mk << 'EOF'
INC=%%%%

CC=gcc

NAME=mlx-test
SRC=main.c
OBJ=$(SRC:.c=.o)

CFLAGS= -I$(INC) -O3 -I..

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) -L.. -lmlx -L/usr/lib -lXext -lX11 -lm -lbsd

clean:
	rm -f $(NAME) $(OBJ) *~ core *.core
EOF
echo -e "${GREEN}Makefile.mk created successfully!${NC}"

# Create a simple main.c test file
echo -e "${YELLOW}Creating main.c test file...${NC}"
cat > libraries/mlx/test/main.c << 'EOF'
#include <mlx.h>

int main(void)
{
    void *mlx;
    void *win;

    mlx = mlx_init();
    if (!mlx)
        return (1);
    win = mlx_new_window(mlx, 500, 500, "MLX Test");
    if (!win)
        return (1);
    mlx_loop(mlx);
    return (0);
}
EOF
echo -e "${GREEN}Test file created successfully!${NC}"

# Modify the configure script to handle missing test directory
if [ -f "libraries/mlx/configure" ]; then
    echo -e "${YELLOW}Checking configure script...${NC}"
    # Create a backup of the original configure script if it doesn't exist
    if [ ! -f "libraries/mlx/configure.bak" ]; then
        cp libraries/mlx/configure libraries/mlx/configure.bak
    fi
    
    # Restore from backup to ensure clean state
    cp libraries/mlx/configure.bak libraries/mlx/configure
    
    # Modify the configure script to handle errors more gracefully
    sed -i 's|cat test/Makefile.mk|cat test/Makefile.mk 2>/dev/null|g' libraries/mlx/configure || true
    
    echo -e "${GREEN}Configure script modified successfully!${NC}"
fi

# Compile the project
echo -e "${YELLOW}Compiling the project...${NC}"
make clean || true
make

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo -e "${GREEN}Setup completed successfully!${NC}"
    echo -e "${YELLOW}You can now run the game with:${NC} ./cub3D maps/example.cub"
    echo -e "${YELLOW}To test if the MLX library is working correctly, run:${NC} ./cub3D --test-mlx"
    echo -e "${YELLOW}To force the use of the local MLX library, run:${NC} make test-local-mlx"
else
    echo -e "${RED}Compilation failed. Please check the error messages above.${NC}"
    exit 1
fi

exit 0 