/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                      :+:      :+:    :+:   */
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

void    draw_square(t_file *map, int col, int row, int color)
{
    int x, y;
    int start_x = col * TILE_SCALE;
    int start_y = row * TILE_SCALE;

    y = start_y;
    while (y < start_y + TILE_SCALE)
    {
        x = start_x;
        while (x < start_x + TILE_SCALE)
        {
            put_pixel_minimap(map, x, y, color); // White for walls
            x++;
        }
        y++;
    }
}

void    draw_wall(t_file *map, int col, int row)
{
    draw_square(map, col, row, COLOR_BLACK);
}

void    draw_floor(t_file *map, int col, int row)
{
    draw_square(map, col, row, COLOR_WHITE);
}

void    draw_player(t_file *map, int col, int row)
{
    draw_square(map, col, row, COLOR_GREEN);
}

void    draw_unknown(t_file *map, int col, int row)
{
    draw_square(map, col, row, COLOR_WHITE);
}