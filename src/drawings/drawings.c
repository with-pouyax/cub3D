/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawings.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:27:25 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/15 15:27:25 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//first we put pixel in to the buffer and next we gonna display it
void	put_pixel(int x, int y, int color, t_mlx *game)
{
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	int i = y * game->img_ptr.line_length + x * game->img_ptr.bits_per_pixel / 8;
	game->img_ptr.addr[i] = color &  0xFF;
	game->img_ptr.addr[i + 1] = (color >> 8) &  0xFF;
	game->img_ptr.addr[i + 2] = (color >> 16) &  0xFF;
	
}


// void	draw_player(int x, int y, int size, int color, t_mlx *game)
// {
// 	for (int i = 0; i < size; i++)
// 		put_pixel(x + i, y, color, game);
// 	for (int i = 0; i < size; i++)
// 		put_pixel(x, y + i, color, game);
// 	for (int i = 0; i < size; i++)
// 		put_pixel(x + size, y + i, color, game);
// 	for (int i = 0; i < size; i++)
// 		put_pixel(x + i, y + size, color, game);
// }

void draw_tile(int x, int y, int size, int color, t_file *game)
{
	for (int dy = 0; dy < size; dy++)
	{
		for (int dx = 0; dx < size; dx++)
		{
			int px = x + dx;
			int py = y + dy;
			if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
			{
				int offset = py * game->mlx.img_ptr.line_length + px * (game->mlx.img_ptr.bits_per_pixel / 8);
				game->mlx.img_ptr.addr[offset] = color & 0xFF;
				game->mlx.img_ptr.addr[offset + 1] = (color >> 8) & 0xFF;
				game->mlx.img_ptr.addr[offset + 2] = (color >> 16) & 0xFF;
			}
		}
	}
}


void draw_player(t_player *player, t_file *game)
{
	int px = player->x * BLOCK;
	int py = player->y * BLOCK;
	draw_tile(px, py, BLOCK / 2, COLOR_GREEN, game); // small green dot
}
void draw_map(t_file *game)
{
	char **map = game->game_map;
	for (int y = 0; map[y]; y++)
	{
		for (int x = 0; map[y][x]; x++)
		{
			char tile = map[y][x];
			int color;

			if (tile == '1')
				color = 0x3333FF; // wall
			else if (tile == '0')
				color = 0xFFFFFF; // floor
			else if (tile == 'P')
				color = COLOR_GREEN; // initial player position (optional)
			else
				color = 0xFF00FF; // unknown/debug

			draw_tile(x * BLOCK, y * BLOCK, BLOCK, color, game);
		}
	}
}

void clean_img(t_mlx *game)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			put_pixel(x, y, 0, game);
		}
	}
}
