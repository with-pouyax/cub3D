# Cub3D - 3D Raycasting Game

![Cub3D Preview](https://raw.githubusercontent.com/42Paris/minilibx-linux/master/mlx.png)

## 🎮 Project Overview

Cub3D is a first-person 3D game engine inspired by the iconic Wolfenstein 3D game, the first FPS ever. This project is part of the 42 school curriculum and focuses on raycasting techniques to create a 3D perspective in a 2D map.

⚠️ **NOTE: This project is currently under construction and not yet finished** ⚠️

## 🚀 Features

- Smooth window management
- Textured walls with different textures for each direction (North, South, East, West)
- Floor and ceiling colors
- Player movement (forward, backward, left, right)
- Camera rotation
- Collision detection
- Map parsing from a configuration file

## 🗺️ Map Configuration

Maps are defined in `.cub` files with the following elements:

```
NO ./path_to_north_texture.xpm
SO ./path_to_south_texture.xpm
WE ./path_to_west_texture.xpm
EA ./path_to_east_texture.xpm

F R,G,B    # Floor RGB color
C R,G,B    # Ceiling RGB color

# Map layout (1 = wall, 0 = empty space, N/S/E/W = player starting position and orientation)
1111111111111
1000000000001
1000000000001
1000000N00001
1000000000001
1111111111111
```

## 🛠️ Allowed Functions

This project restricts the use of external functions. Here are the allowed functions:

- `open`, `close`, `read`, `write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit`
- All functions of the math library (`-lm` compiler option)
- All functions of the MinilibX graphics library

## 🔧 Installation and Usage

### Prerequisites
- GCC compiler
- Make
- X11 development libraries
- MinilibX library

### Compilation
```bash
make
```

### Running the game
```bash
./cub3D path_to_map.cub
```

## 🧪 Testing

The project includes validation for:
- Map integrity (closed walls)
- File format validation
- Texture loading
- Color parsing
- Memory management

## 📝 Project Structure

```
.
├── includes/       # Header files
├── libraries/      # External libraries (libft, minilibx)
├── maps/           # Example map files
├── src/            # Source code
│   ├── parsing/    # Map parsing functions
│   ├── rendering/  # Raycasting and rendering
│   ├── utils/      # Utility functions
│   └── main.c      # Entry point
├── Makefile        # Build configuration
└── README.md       # This file
```

## 🔍 Implementation Details

The project implements:
1. **Map Parsing**: Reading and validating the map file
2. **Raycasting**: Calculating wall distances and heights
3. **Rendering**: Drawing walls, floor, and ceiling
4. **Player Movement**: Handling keyboard inputs for movement
5. **Collision Detection**: Preventing the player from walking through walls

## 🚧 Current Status

The project is currently in development. Completed components:
- Map parsing and validation
- Basic structure setup

Components under construction:
- Raycasting implementation
- Texture rendering
- Player movement
- Game loop

## 📚 Resources

- [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D)
- [Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [MinilibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)

## 👥 Contributors

This project is being developed as part of the 42 curriculum.

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details. 