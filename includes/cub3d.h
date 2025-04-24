/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:02:35 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/14 09:13:21 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1940
# define HEIGHT 1280

# define COLOR_BLUE    0x3333FF
# define COLOR_WHITE   0xFFFFFF
# define COLOR_GREEN   0x7FFF00
# define COLOR_MAGENTA 0xFF00FF
# define COLOR_BLACK   0x000000
# define COLOR_RED   0xDC143C

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>

# include "../libraries/libft/libft.h"
# include "../libraries/mlx/mlx.h"

#define MOVE_SPEED 0.09
#define ROTATE_SPEED 0.09

# define W 		119
# define A 		97
# define S 		115
# define D 		100
# define ESP 	65307
# define LEFT 	65361
# define RIGHT 	65363

# define TILE_SCALE 7 // Define the size of a block (adjust this based on your map)
# define MAP_WIDTH 24  // Adjust this based on the number of columns in your map
# define MAP_HEIGHT 24 // Adjust this based on the number of rows in your map

# define PI 3.14159265359

typedef enum e_direction
{
    FORWARD,
    BACKWARD,
    LEFTWARD,
    RIGHTWARD
}   t_direction;

enum	e_directions
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

typedef struct s_colors
{
	int	floor;
	int	ceiling;
}	t_colors;

typedef struct s_texture_paths
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_texture_paths;

typedef struct s_img
{
	void	*img;
	char	*path;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		w;
	int		h;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img_ptr;
}	t_mlx;

typedef struct s_player
{
    float 	x;
    float 	y;
    // float 	angle;
	// bool	key_up;
	// bool	key_down;
	// bool	key_left;
	// bool	key_right;
	// bool 	left_rotate;
    // bool 	right_rotate;
	// int 	speed;        // Player movement speed
    // float 	angle_speed;  // Rotation speed
}	t_player;

typedef struct s_file
{
	char			**raw_file;
	t_texture_paths	textures;
	t_colors		colors;
	t_img 			image[5];
	char			**game_map;
	int				map_height;
	int				map_width;
	char			player_dir;
	double			dir_x_face;
	double			dir_y_face;
	double			ray_screen_pos;
	double			ray_dir_x;
	double			ray_dir_y;
	double			distance_to_x;
	double			distance_to_y;
	double			dist_from_next_wall_x;
	double			dist_from_next_wall_y;
	double			perpendicular_wall_distance;
	int				ray_travel_x;
	int				ray_travel_y;
	int				hit_vertical_wall;
	int				hit_horizontal_wall;
	int				start_wall;
	int				end_wall;
	int				texture_cordinat_x;
	int				texture_cordinat_y;
	double			pos_hit_wall_x;
	double			step;
	double			tex_position;
	double			player_x;
	double			player_y;
	int				map_tile_x;  //refers to the current tile
	int				map_tile_y;
	double			plane_x;
	double			plane_y;
	t_mlx			mlx;
	t_player        player;
	t_img			minimap_img;
}	t_file;

typedef struct s_dir_flags
{
	int	no;
	int	so;
	int	we;
	int	ea;
}	t_dir_flags;

typedef struct s_color_flags
{
	int	floor;
	int	ceiling;
}	t_color_flags;

typedef struct s_coord
{
	int	i;
	int	j;
}	t_coord;

typedef struct s_parse_data
{
	t_dir_flags		*dir_flags;
	t_color_flags	*color_flags;
	int				*found_map_start;
}	t_parse_data;

/* Error handling functions */
void	ft_perror(char *msg, int err);
void	pexit(char *msg, int err, int exit_code);

/* File handling functions */
int		extentions_check(char *file);
int		arg_check(int ac);
void	safe_close(int fd);
int		file_length(char *file_name);
int		copy_file(char *file_name, char **file, int file_len);
char	*get_string(int *file_len, char **av);

/* Map validation functions */
int		map_is_empty(char **map);
int		is_last_line_empty(char **map);
void	skip_empty_lines(char **map, int *index);
int		no_xpm_extension(char *line);
int		is_direction(char *line, char *dir);

/* Path and RGB extraction functions */
int		extract_and_assign_path(char *line, char **dest);
int		wrong_rgb(char *line);
int		parse_rgb_value(char *str, int *i);
int		extract_rgb(char *line, int *rgb_value);

/* Map character validation functions */
int		not_valid_char(char c, int *player_count, t_file *map, t_coord *pos);
int		check_player_count(int player_count);
int		basic_map_check(t_file *map, char **raw_file, int *index);

/* Map dimension and copying functions */
int		get_map_height(char **map, int start_index);
char	*ft_strdup_map(char *str);
void	free_game_map(char **game_map, int last_index);
size_t	update_max_width(char **map, int i, size_t max_width);
int		copy_map_lines(t_file *map, int index, int height);
int		copy_map(t_file *map, int index);
int		wrong_ratio(char **map);
int		not_map(t_file *map, int *index);

/* Debug and display functions */
void	print_whole_structure_in_order(t_file *map);

/* Texture and color line processing functions */
int		is_texture_line(char *line);
int		is_color_line(char *line);
int		get_identifier_position(char *line);
int		process_no_texture(t_file *map, char *line, t_dir_flags *dir_flags);
int		process_so_texture(t_file *map, char *line, t_dir_flags *dir_flags);
int		process_we_texture(t_file *map, char *line, t_dir_flags *dir_flags);
int		process_ea_texture(t_file *map, char *line, t_dir_flags *dir_flags);
int		process_texture_line(t_file *map, char *line, t_dir_flags *dir_flags);
int		process_floor_color(t_file *map, char *line, \
t_color_flags *color_flags);
int		process_ceiling_color(t_file *map, char *line, \
t_color_flags *color_flags);
int		process_color_line(t_file *map, char *line, t_color_flags *color_flags);

/* Parsing functions */
int		check_all_elements_present(t_dir_flags *dir_flags, \
t_color_flags *color_flags);
int		process_line(t_file *map, char *line, t_parse_data *data);
void	init_parse_data(t_parse_data *data, t_dir_flags *dir_flags, \
t_color_flags *color_flags, int *found_map_start);
int		process_current_line(t_file *map, int *index, t_parse_data *data);
int		parse_textures_and_colors(t_file *map, int *index, \
t_dir_flags *dir_flags, t_color_flags *color_flags);
int		parse_map(t_file **map);
int		is_empty_line(char *line);
void	trim_empty_lines(char ***map);
int		parse_args(int ac, char **av, t_file **map);

/* Initialization and cleanup functions */
int		init_map(t_file **map);
void	clean_string_array(char ***array);
void	clean_texture_paths(t_texture_paths *textures);
void	cleanup_mlx(t_file *map);
void	cleanup(t_file **map);

/* MLX initialization and setup functions */
int		init_map_mlx(t_file **map);
int		init_mlx(t_file **map);
int		create_window(t_file **map);
int		create_image_buffer(t_file **map);
int		start_game(t_file **map);

/* Event handling functions */
int		handle_esc_press(t_file **map);
int		handle_x_press(int keycode, t_file **map);
int		set_event_hooks(t_file **map);
int		game_loop(t_file **map);

/* Wall checking functions */
int		is_valid_position(char **map, int row, int col);
int		is_space_or_tab(char c);
int		is_fillable(char c);
int		is_at_edge(char **map, int row, int col);
int		is_valid_for_fill(char **map, int row, int col, int *found_edge);
void	flood_fill(char **map, int row, int col, int *found_edge);
char	**backup_map(char **map);
int		restore_from_backup(char **map, char **backup);
void	free_backup(char **backup);
int		check_position(char **map, char **backup, int row, int col);
int		check_walls(char **map);

// Function declaration from test_mlx.c
int	test_mlx(void);

// Function declarations from mlx_init.c
int	init_map_mlx(t_file **map);
int	init_mlx(t_file **map);
int	create_window(t_file **map);
int	create_image_buffer(t_file **map);
int	start_game(t_file **map);

// Function declarations from mlx_events.c
int	handle_x_press(int keycode, t_file **map);
int	set_event_hooks(t_file **map);
int	game_loop(t_file **map);

//movements
void clean_img(t_mlx *game);
// void update_player_state(t_player *player);
// void perform_move(t_player *player);
// void perform_rotation(t_player *player);
int    	init_minimap(t_file **map);
void    draw_square(t_file *map, int col, int row, int color);
void    draw_wall(t_file *map, int col, int row);
void    draw_floor(t_file *map, int col, int row);
void    draw_player(t_file *map, int col, int row);
void    draw_unknown(t_file *map, int col, int row);
void    put_pixel_minimap(t_file *map, int x, int y, int color);
int    	recasting(t_file **map);
void	img_pix_put(t_file *map, int x, int y, int color);
int	assign_texture_paths_to_images(t_file *map);

//move key words
void    move_up_down(t_file *map, t_direction direction);
void    move_right_left(t_file *map, t_direction direction);
void 	move_forward(t_file *map);
void 	move_backward(t_file *map);
void 	move_leftward(t_file *map);
void 	move_rightward(t_file *map);
void 	rotate_left(t_file *map);
void 	rotate_right(t_file *map);

int 	load_image(t_file **map, int index);
int 	get_image_address(t_file **map, int index);
void 	draw_floor_3d(t_file **map, int x, int y);
void 	draw_sky_3d(t_file **map, int x, int y);
void 	img_pix_put(t_file *map, int x, int y, int color);
int		handle_esc_press(t_file **map);
int		handle_x_press(int keycode, t_file **map);
int 	handle_keypress(int keycode, t_file **map);
int		set_event_hooks(t_file **map);

void    dda_implimentation(t_file **map);
void calculate_perpwalldist(t_file **map);
void    draw_col(t_file *map, int x);
void    calculate_wall_hight(t_file *map, int *wall_height);
void texture_definition(t_file *map, int wall_hight);
void draw_column_pixels(t_file *map, int x);
void	draw(t_file *map, int x, int texture);
int	get_color(t_file *map, int i);

void    cleanup(t_file **map);
void    cleanup_mlx(t_file *map);

#endif
