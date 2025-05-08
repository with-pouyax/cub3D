/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoushma <mhoushma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:27:25 by pghajard          #+#    #+#             */
/*   Updated: 2025/05/08 12:26:05 by mhoushma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
// draws a square on the minimap
// The function calculates the starting x and y coordinates of the square
// map->minimap_scale: This determines the size of each square on the minimap 
// continuing until it reaches the bottom edge of the square 
// (start_y + map->minimap_scale)
void	draw_square(t_file *map, int col, int row, int color)
{
	int	x;
	int	y;
	int	start_x;
	int	start_y;

	if (map->minimap_scale == 0)
		return ;
	start_x = col * map->minimap_scale;
	start_y = row * map->minimap_scale;
	y = start_y;
	while (y < start_y + map->minimap_scale)
	{
		x = start_x;
		while (x < start_x + map->minimap_scale)
		{
			put_pixel_minimap(map, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_wall(t_file *map, int col, int row)
{
	draw_square(map, col, row, COLOR_BLUE);
}

void	draw_floor(t_file *map, int col, int row)
{
	draw_square(map, col, row, COLOR_WHITE);
}

void	draw_player(t_file *map, int col, int row)
{
	draw_square(map, col, row, COLOR_RED);
}

void	draw_unknown(t_file *map, int col, int row)
{
	draw_square(map, col, row, COLOR_BLUE);
}
