/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:27:25 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/15 15:27:25 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// pixel for--> Calculate the address of the pixel based on row and column
// (int *)pixel casts the pixel pointer (
// why we cast pixel to the *int --> A char is typically 1 byte.
// An int is typically 4 bytes on most systems (32-bit), which is the typical
//  size
//  for a color value like 0xRRGGBB or 0xAARRGGBB (a 32-bit value).
void	put_pixel_minimap(t_file *map, int x, int y, int color)
{
	char	*pixel;

	if (y < 0 || y >= HEIGHT * TILE_SCALE || x < 0 || x >= WIDTH * TILE_SCALE)
		return ;
	pixel = (map->minimap_img.addr + (y * map->minimap_img.line_length
				+ x * (map->minimap_img.bits_per_pixel / 8)));
	*(int *)pixel = color;
}

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
