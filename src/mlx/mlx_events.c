/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:27:25 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/15 15:27:25 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//while (x ...)  --> This goes from the left to right side of the screen.
// while (y ...) --> This ensures every pixel on the screen is visited once.
// hight / 2 --> The screen is split in half horizontally:
// - If the pixel is in the top half, it is part of the sky.
// - Else, it is part of the floor.
void	render_sky_floor(t_file **map)
{
	int	x;
	int	y;
	int	middle_of_screen;

	x = 0;
	middle_of_screen = HEIGHT / 2;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y < middle_of_screen)
			{
				draw_sky_3d(map, x, y);
			}
			else
			{
				draw_floor_3d(map, x, y);
			}
			y++;
		}
		x++;
	}
}

void	update_player_state(t_player *player, t_file *map)
{
	if (player->key_up)
		move_forward(map);
	if (player->key_down)
		move_backward(map);
	if (player->key_left)
		move_leftward(map);
	if (player->key_right)
		move_rightward(map);
	if (player->left_rotate)
		rotate_left(map);
	if (player->right_rotate)
		rotate_right(map);
}

int	game_loop(t_file **map)
{
	t_player    *player;

	player = &(*map)->player;
	update_player_state(player, *map);
	render_sky_floor(map);
	recasting(map);
	mlx_put_image_to_window(
		(*map)->mlx.mlx,
		(*map)->mlx.win,
		(*map)->image[4].img,
		0, 0);
	mlx_put_image_to_window(
		(*map)->mlx.mlx,
		(*map)->mlx.win,
		(*map)->minimap_img.img,
		10, 10);
	return (0);
}
