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
// An int is typically 4 bytes on most systems (32-bit), which is the typical size
//  for a color value like 0xRRGGBB or 0xAARRGGBB (a 32-bit value).
void    put_pixel_minimap(t_file *map, int x, int y, int color)
{
    char    *pixel;

    if (y < 0 || y >= map->map_height * TILE_SCALE || x < 0 || x >= map->map_width * TILE_SCALE)
        return;
    pixel = (map->minimap_img.addr + (y * map->minimap_img.line_length 
    + x * (map->minimap_img.bits_per_pixel / 8)));
    *(int *)pixel = color;
}

void    draw_minimap(t_file *map)
{
    int row;
    int col;

    row = 0;
    col = 0;
    while (map->game_map[row])
    {
        col = 0;
        while(map->game_map[row][col])
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

int    init_minimap(t_file **map)
{
    int width;
    int height;

    width = (*map)->map_width * TILE_SCALE;
    height = (*map)->map_height * TILE_SCALE;
    // printf("[DEBUG] Minimap dimensions: width=%d, height=%d\n", width, height);
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