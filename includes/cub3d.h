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

# define WIDTH 1200
# define HEIGHT 720
# define COLOR_GREEN 0x00FF00

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>

# include "../libraries/libft/libft.h"
# include "../libraries/mlx/mlx.h"

#define MOVE_SPEED 5
#define ROTATE_SPEED 0.05

#define W 119
#define A 97
#define S 115
#define D 100
#define ESP 65307
#define LEFT 65361
#define RIGHT 65363


#define PI 3.14159265359
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
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img_ptr;
}	t_mlx;

typedef struct s_player
{
    float x;
    float y;
    float angle;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool 	left_rotate;
    bool 	right_rotate;
	int 	speed;        // Player movement speed
    float 	angle_speed; // Rotation speed
}	t_player;

typedef struct s_file
{
	char			**raw_file;
	t_texture_paths	textures;
	t_colors		colors;
	char			**game_map;
	int				map_height;
	int				map_width;
	char			player_dir;
	int				player_x;
	int				player_y;
	t_mlx			mlx;
	t_player        player;
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
void	init_player(t_file *map);
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
void	draw_square(int x, int y, int size, int color, t_mlx *game);
void	put_pixel(int x, int y, int color, t_mlx *game);
void clean_img(t_mlx *game);
void update_player_state(t_player *player);
void perform_move(t_player *player);
void perform_rotation(t_player *player);

#endif
