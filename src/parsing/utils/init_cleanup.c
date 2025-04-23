/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:29:57 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/13 16:35:11 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int init_map(t_file **map)
{
    int i;

    *map = malloc(sizeof(t_file));
    if (!*map)
        return (ft_perror("malloc", errno), 1);
    (*map)->raw_file = NULL;
    (*map)->textures.north = NULL;
    (*map)->textures.south = NULL;
    (*map)->textures.west = NULL;
    (*map)->textures.east = NULL;
    (*map)->colors.floor = 0;
    (*map)->colors.ceiling = 0;
    (*map)->game_map = NULL;
    (*map)->map_height = 0;
    (*map)->map_width = 0;
    (*map)->player_dir = '\0';
    (*map)->player_x = 0;
    (*map)->player_y = 0;
    (*map)->dir_x_face = 0.0;
    (*map)->dir_y_face = 0.0;
    (*map)->ray_screen_pos = 0.0;
    (*map)->ray_dir_x = 0.0;
    (*map)->ray_dir_y = 0.0;
    (*map)->distance_to_x = 0.0;
    (*map)->distance_to_y = 0.0;
    (*map)->dist_from_next_wall_x = 0.0;
    (*map)->dist_from_next_wall_y = 0.0;
    (*map)->perpendicular_wall_distance = 0.0;
    (*map)->ray_travel_x = 0;
    (*map)->ray_travel_y = 0;
    (*map)->hit_vertical_wall = 0;
    (*map)->hit_horizontal_wall = 0;
    (*map)->map_tile_x = 0;
    (*map)->map_tile_y = 0;
    (*map)->plane_x = 0.0;
    (*map)->plane_y = 0.0;
    (*map)->mlx.mlx = NULL;
    (*map)->mlx.win = NULL;
    (*map)->mlx.img_ptr.img = NULL;
    (*map)->player.x = 0.0;
    (*map)->player.y = 0.0;
    // (*map)->player.angle = 0.0;
    // (*map)->player.key_up = false;
    // (*map)->player.key_down = false;
    // (*map)->player.key_left = false;
    // (*map)->player.key_right = false;
    // (*map)->player.left_rotate = false;
    // (*map)->player.right_rotate = false;
    // (*map)->player.speed = 0;
    // (*map)->player.angle_speed = 0.0;
    i = 0;
    while (i < 5)
    {
        (*map)->image[i].img = NULL;
        (*map)->image[i].path = NULL;
        i++;
    }
    (*map)->minimap_img.img = NULL;
    return (0);
}

void	clean_string_array(char ***array)
{
	int	i;

	if (!array || !*array)
		return ;
	i = 0;
	while ((*array)[i])
		free((*array)[i++]);
	free(*array);
	*array = NULL;
}

void	clean_texture_paths(t_texture_paths *textures)
{
	if (!textures)
		return ;
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->west)
		free(textures->west);
	if (textures->east)
		free(textures->east);
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
}

void	cleanup_mlx(t_file *map)
{
	if (map->mlx.img_ptr.img)
		mlx_destroy_image(map->mlx.mlx, map->mlx.img_ptr.img);
	if (map->mlx.win)
		mlx_destroy_window(map->mlx.mlx, map->mlx.win);
	if (map->mlx.mlx)
	{
		mlx_destroy_display(map->mlx.mlx);
		free(map->mlx.mlx);
	}
}

void	cleanup(t_file **map)
{
	if (!map || !*map)
		return ;

	// Clean up MLX resources first
	cleanup_mlx(*map);
	
	// Then clean up other resources
	clean_string_array(&((*map)->raw_file));
	clean_string_array(&((*map)->game_map));
	clean_texture_paths(&((*map)->textures));
	free(*map);
	*map = NULL;
}
