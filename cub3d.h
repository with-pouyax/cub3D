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
	int player_x; // player position
	int player_y; // player position
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

typedef struct s_coord
{
	int i;
	int j;
} t_coord;

typedef struct s_parse_data
{
	t_dir_flags *dir_flags;
	t_color_flags *color_flags;
	int *found_map_start;
} t_parse_data;

int check_walls(char **map);

#endif
