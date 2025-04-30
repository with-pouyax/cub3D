/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:27:25 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/15 15:27:25 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// The origin (0, 0) is at the top-left of the screen or image:
// So if you increase Y, you're actually moving downward on the screen.
// is different from axis in the math word
// the start point (row, col) is top_left
// then row + i increase ---> to the right
// and col + j increase --> to the down
// to draw the square for each pixel
// Don't draw minimap if scale is 0
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
	draw_square(map, col, row, COLOR_BLACK);
}
