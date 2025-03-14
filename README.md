# Cub3D
![Cub3D cover](https://media1.giphy.com/media/v1.Y2lkPTc5MGI3NjExOWJ0NG92Nnh1cnBlY281djA1Njk5MG5keGV3bXl5Yzl6dHg5Nzd0eiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/dKa9QCD0n7JeRRui8o/giphy.gif)
A 3D game using raycasting, inspired by Wolfenstein 3D.

## Description

Cub3D is a first-person 3D game built using the raycasting technique. This project is part of the 42 school curriculum and aims to recreate the classic Wolfenstein 3D game mechanics.

## Features

- Textured walls with different textures for each direction (North, South, East, West)
- Collision detection
- Player movement (forward, backward, strafe left, strafe right)
- Camera rotation (left, right)
- Customizable map through a simple file format

## Prerequisites

- GCC compiler
- Make
- X11 libraries (for Linux) or AppKit/OpenGL (for macOS)

### Dependencies for Linux

```bash
sudo apt-get install libxext-dev libxrandr-dev libx11-dev libbsd-dev libssl-dev
```

## Installation

### Quick Setup

The easiest way to set up the project is to use the provided setup script:

```bash
./setup.sh
```

This script will:
1. Install necessary dependencies based on your OS
2. Create required directories
3. Clone the MLX library if it doesn't exist
4. Compile the project

### Manual Setup

1. Clone the repository:

```bash
git clone https://github.com/yourusername/cub3d.git
cd cub3d
```

2. Compile the project:

```bash
make
```

The Makefile will automatically:
- Check if MLX is installed on your system
- If not, it will clone and compile the MLX library from the official repository
- Compile the Cub3D project

### Testing MLX

You can test if the MLX library is working correctly by running:

```bash
./cub3D --test-mlx
```

If you're running in a remote environment without a display server, you'll see a message indicating that the MLX library is linked correctly but requires a display server to use it.

If you want to force the use of the local MLX library (even if it's installed on your system), you can run:

```bash
make test-local-mlx
```

This will:
1. Clean any existing MLX library
2. Clone the MLX library if it doesn't exist
3. Compile the MLX library
4. Compile the project using the local MLX library

## Usage

Run the program with a map file:

```bash
./cub3D maps/example.cub
```

### Map Format

The map file should follow this format:

```
NO ./path/to/north_texture.xpm
SO ./path/to/south_texture.xpm
WE ./path/to/west_texture.xpm
EA ./path/to/east_texture.xpm

F R,G,B
C R,G,B

1111111111
1000000001
1000N00001
1000000001
1111111111
```

Where:
- `NO`, `SO`, `WE`, `EA` specify the path to the textures for each direction
- `F` specifies the floor color in RGB format
- `C` specifies the ceiling color in RGB format
- The map is composed of:
  - `0` for empty spaces
  - `1` for walls
  - `N`, `S`, `E`, or `W` for the player's starting position and orientation

## Controls

- `W`: Move forward
- `S`: Move backward
- `A`: Strafe left
- `D`: Strafe right
- `←`: Rotate camera left
- `→`: Rotate camera right
- `ESC`: Exit the game

## Cleaning Up

To remove object files:

```bash
make clean
```

To remove object files and the executable:

```bash
make fclean
```

To rebuild the project:

```bash
make re
```

## Credits

This project was created by pouya as part of the 42 school curriculum.

## License

This project is licensed under the MIT License - see the LICENSE file for details. 
