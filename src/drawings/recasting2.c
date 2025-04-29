/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recasting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:27:25 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/15 15:27:25 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
//is the exact position (decimal) where the ray hit the wall on the face of 
// the wall tile, from 0.0 to 1.0.
void	texture_definition(t_file *map, int wall_hight)
{
	if (map->hit_vertical_wall == 1)
		map->pos_hit_wall_x = map->player_y
			+ map->perpendicular_wall_distance * map->ray_dir_y;
	else if (map->hit_horizontal_wall == 1)
		map->pos_hit_wall_x = map->player_x
			+ map->perpendicular_wall_distance * map->ray_dir_x;
	map->pos_hit_wall_x -= floor(map->pos_hit_wall_x);
	map->texture_cordinat_x = map->pos_hit_wall_x * 128;
	if ((map->hit_vertical_wall == 1 && map->ray_dir_x < 0))
		map->texture_cordinat_x = 128 - map->texture_cordinat_x - 1;
	if (map->hit_horizontal_wall == 1 && map->ray_dir_y > 0)
		map->texture_cordinat_x = 128 - map->texture_cordinat_x - 1;
	map->step = 1.0 * 128 / wall_hight;
	map->tex_position = (map->start_wall
			- (HEIGHT / 2 - wall_hight / 2)) * map->step;
}

void	calculate_wall_hight(t_file *map, int *wall_height)
{
	*wall_height = HEIGHT / map->perpendicular_wall_distance;
	map->start_wall = -*wall_height / 2 + HEIGHT / 2;
	if (map->start_wall < 0)
		map->start_wall = 0;
	map->end_wall = *wall_height / 2 + HEIGHT / 2;
	if (map->end_wall >= HEIGHT)
		map->end_wall = HEIGHT - 1;
}

//calculate_wall_hight : calculates how tall the wall slice should 
// appear on screen
//figuring out which part of the wall texture to draw.
//Draw each pixel of the column
//Choose correct wall texture
void	draw_col(t_file *map, int x)
{
	int	wall_height;

	calculate_wall_hight(map, &wall_height);
	texture_definition(map, wall_height);
	draw_column_pixels(map, x);
}

void	calculate_perpwalldist(t_file **map)
{
	if ((*map)->hit_vertical_wall == 1)
		(*map)->perpendicular_wall_distance
			= ((*map)->dist_from_next_wall_x - (*map)->distance_to_x);
	else if ((*map)->hit_horizontal_wall == 1)
		(*map)->perpendicular_wall_distance
			= ((*map)->dist_from_next_wall_y - (*map)->distance_to_y);
}

//ray will continue to step through the grid cells until it hits wall (== 1)
void	dda_implimentation(t_file **map)
{
	int	hit_wall;

	hit_wall = 0;
	while (hit_wall == 0)
	{
		if ((*map)->dist_from_next_wall_x < (*map)->dist_from_next_wall_y)
		{
			(*map)->dist_from_next_wall_x += (*map)->distance_to_x;
			(*map)->map_tile_x += (*map)->ray_travel_x;
			(*map)->hit_vertical_wall = 1;
			(*map)->hit_horizontal_wall = 0;
		}
		else
		{
			(*map)->dist_from_next_wall_y += (*map)->distance_to_y;
			(*map)->map_tile_y += (*map)->ray_travel_y;
			(*map)->hit_vertical_wall = 0;
			(*map)->hit_horizontal_wall = 1;
		}
		if ((*map)->game_map[(*map)->map_tile_y][(*map)->map_tile_x] == '1')
			hit_wall = 1;
	}
}
