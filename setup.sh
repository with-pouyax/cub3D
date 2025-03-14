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

# Compile the project
echo -e "${YELLOW}Compiling the project...${NC}"
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