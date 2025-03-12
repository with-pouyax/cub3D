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

/* Function prototypes */
int	check_walls(char **map);
int	is_valid_position(char **map, int row, int col);
int	is_space_or_tab(char c);
void	flood_fill(char **map, int row, int col, int *found_edge);
int	parse_textures_and_colors(t_file *map, int *index, 
	t_dir_flags *dir_flags, t_color_flags *color_flags);
int	process_line(t_file *map, char *line, t_parse_data *data);
int	process_texture_line(t_file *map, char *line, t_dir_flags *dir_flags);
int	process_no_texture(t_file *map, char *line, t_dir_flags *dir_flags);
int	process_so_texture(t_file *map, char *line, t_dir_flags *dir_flags);
int	process_we_texture(t_file *map, char *line, t_dir_flags *dir_flags);
int	process_ea_texture(t_file *map, char *line, t_dir_flags *dir_flags);
int	process_color_line(t_file *map, char *line, t_color_flags *color_flags);
int	process_floor_color(t_file *map, char *line, t_color_flags *color_flags);
int	process_ceiling_color(t_file *map, char *line, t_color_flags *color_flags);
void	init_parse_data(t_parse_data *data, t_dir_flags *dir_flags,
	t_color_flags *color_flags, int *found_map_start);
int	process_current_line(t_file *map, int *index, t_parse_data *data);
int	get_identifier_position(char *line);
int	is_empty_line(char *line);
void	trim_empty_lines(char ***map);

#endif
