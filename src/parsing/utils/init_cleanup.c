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

void	init_textures(t_texture_paths *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
}

void	init_player_and_raycasting(t_file *map)
{
	map->player_dir = '\0';
	map->player_x = 0;
	map->player_y = 0;
	map->dir_x_face = 0.0;
	map->dir_y_face = 0.0;
	map->ray_screen_pos = 0.0;
	map->ray_dir_x = 0.0;
	map->ray_dir_y = 0.0;
	map->distance_to_x = 0.0;
	map->distance_to_y = 0.0;
	map->dist_from_next_wall_x = 0.0;
	map->dist_from_next_wall_y = 0.0;
	map->perpendicular_wall_distance = 0.0;
	map->ray_travel_x = 0;
	map->ray_travel_y = 0;
	map->hit_vertical_wall = 0;
	map->hit_horizontal_wall = 0;
	map->map_tile_x = 0;
	map->map_tile_y = 0;
	map->plane_x = 0.0;
	map->plane_y = 0.0;
}

void	init_images(t_file *map)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		map->image[i].img = NULL;
		map->image[i].path = NULL;
		i++;
	}
	map->minimap_img.img = NULL;
}

//*****************************************************************************
//*                                                                           
//* 1- we allocate memory for the map structure                                
//* 2- we initialize the structures with the correct starting values
//*****************************************************************************
int	init_map(t_file **map)
{
	*map = malloc(sizeof(t_file));
	if (!*map)
		return (ft_perror("malloc", errno), 1);
	(*map)->raw_file = NULL;
	init_textures(&(*map)->textures);
	(*map)->colors.floor = 0;
	(*map)->colors.ceiling = 0;
	(*map)->game_map = NULL;
	(*map)->map_height = 0;
	(*map)->map_width = 0;
	init_player_and_raycasting(*map);
	init_images(*map);
	(*map)->mlx.mlx = NULL;
	(*map)->mlx.win = NULL;
	(*map)->mlx.img_ptr.img = NULL;
	(*map)->player.x = 0.0;
	(*map)->player.y = 0.0;
	return (0);
}
