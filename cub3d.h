#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
# include <fcntl.h>

#include "libraries/libft/libft.h"

typedef struct s_colors
{
	int floor;
	int ceiling;
} t_colors;

typedef struct s_texture_paths
{
	char *north;
	char *south;
	char *west;
	char *east;
} t_texture_paths;

typedef struct s_file
{
	char **raw_file;
	t_texture_paths textures;
	t_colors colors;
	char **game_map;
	int map_height;
	int map_width;
	char player_dir;
	int player_x;
	int player_y;
} t_file;

typedef struct s_dir_flags
{
	int no;
	int so;
	int we;
	int ea;
} t_dir_flags;

typedef struct s_color_flags
{
	int floor;
	int ceiling;
} t_color_flags;

/* Function prototypes */
int	check_walls(char **map);
int	is_valid_position(char **map, int row, int col);
int	is_space_or_tab(char c);
void	flood_fill(char **map, int row, int col, int *found_edge);

#endif
