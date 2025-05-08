/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoushma <mhoushma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:27:25 by pghajard          #+#    #+#             */
/*   Updated: 2025/05/08 11:09:20 by mhoushma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//responsible for drawing a single pixel on the minimap
// if (...)-->ensures the pixel being drawn is within the bounds of minimap
// map->minimap_img.addr:  It points to the first pixel of the image.
// line_length the number of bytes in one row of the image.
// bits_per_pixel-->ndicates how many bits are used to represent a single pixel
// /8 --> converts bits to bytes
//*(int *)pixel--> setting the pixel at (x, y) to the specified color.
void	put_pixel_minimap(t_file *map, int x, int y, int color)
{
	char	*pixel;

	if (y < 0 || y >= HEIGHT * TILE_SCALE || x < 0 || x >= WIDTH * TILE_SCALE)
		return ;
	pixel = (map->minimap_img.addr + (y * map->minimap_img.line_length
				+ x * (map->minimap_img.bits_per_pixel / 8)));
	*(int *)pixel = color;
}

//map->game_map[row][col] refers to accessing a specific cell in the 2D array
void	draw_minimap(t_file *map)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (map->game_map[row])
	{
		col = 0;
		while (map->game_map[row][col])
		{
			if (map->game_map[row][col] == '1')
				draw_wall(map, col, row);
			else if (map->game_map[row][col] == '0')
				draw_floor(map, col, row);
			else if (map->game_map[row][col] == 'N'
			|| map->game_map[row][col] == 'S'
			|| map->game_map[row][col] == 'E'
			|| map->game_map[row][col] == 'W')
				draw_player(map, col, row);
			else
				draw_unknown(map, col, row);
			col++;
		}
		row++;
	}
}

// This function sets the scale of the minimap based on the map dimensions
// The minimap scale is calculated to fit within a maximum pixel size
// is necessary to ensure that the minimap is not too large to be displayed
void	set_minimap_scale(t_file *map)
{
	int	scale_w;
	int	scale_h;
	int	scale;

	scale_w = MINIMAP_MAX_PIXELS / map->map_width;
	scale_h = MINIMAP_MAX_PIXELS / map->map_height;
	if (scale_w < scale_h)
		scale = scale_w;
	else
		scale = scale_h;
	if (scale < MINIMAP_MIN_SCALE)
		scale = 0;
	map->minimap_scale = scale;
}

int	init_minimap(t_file **map)
{
	int	width;
	int	height;

	set_minimap_scale(*map);
	if ((*map)->minimap_scale == 0)
	{
		printf("Minimap too large to display, hiding minimap.\n");
		return (0);
	}
	width = (*map)->map_width * (*map)->minimap_scale;
	height = (*map)->map_height * (*map)->minimap_scale;
	(*map)->minimap_img.img = mlx_new_image((*map)->mlx.mlx, width, height);
	if (!(*map)->minimap_img.img)
		return (1);
	(*map)->minimap_img.addr = mlx_get_data_addr((*map)->minimap_img.img,
			&(*map)->minimap_img.bits_per_pixel,
			&(*map)->minimap_img.line_length,
			&(*map)->minimap_img.endian);
	if (!(*map)->minimap_img.addr)
		return (1);
	draw_minimap((*map));
	return (0);
}
