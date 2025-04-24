/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:27:25 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/15 15:27:25 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	update_minimap(t_file *map, double old_x, double old_y)
{
	draw_square(map, (int)map->player_x, (int)map->player_y, COLOR_RED);
	if ((int)map->player_x != old_x)
		draw_square(map, old_x, old_y, COLOR_WHITE);
	if ((int)map->player_y != old_y)
		draw_square(map, old_x, old_y, COLOR_WHITE);
}

void	move_player(t_file *map, double new_x, double new_y)
{
	if (map->game_map[(int)map->player_y][(int)(map->player_x + new_x)] != '1')
		map->player_x += new_x;
	if (map->game_map[(int)(map->player_y + new_y)][(int)map->player_x] != '1')
		map->player_y += new_y;
}

void	move_player_opposite(t_file *map, double new_x, double new_y)
{
	if (map->game_map[(int)map->player_y][(int)(map->player_x - new_x)] != '1')
		map->player_x -= new_x;
	if (map->game_map[(int)(map->player_y - new_y)][(int)map->player_x] != '1')
		map->player_y -= new_y;
}

void	move_up_down(t_file *map, t_direction direction)
{
	double	old_x;
	double	old_y;
	double	new_x;
	double	new_y;

	old_x = (int)map->player_x;
	old_y = (int)map->player_y;
	new_x = map->dir_x_face * MOVE_SPEED;
	new_y = map->dir_y_face * MOVE_SPEED;
	if (direction == FORWARD)
		move_player(map, new_x, new_y);
	else if (direction == BACKWARD)
		move_player_opposite(map, new_x, new_y);
	if (old_x != map->map_tile_x || old_y != map->map_tile_y)
		update_minimap(map, old_x, old_y);
}

void	move_right_left(t_file *map, t_direction direction)
{
	double	old_x;
	double	old_y;
	double	new_x;
	double	new_y;

	old_x = (int)map->player_x;
	old_y = (int)map->player_y;
	new_x = map->plane_x * MOVE_SPEED;
	new_y = map->plane_y * MOVE_SPEED;
	if (direction == RIGHTWARD)
		move_player(map, new_x, new_y);
	else if (direction == LEFTWARD)
		move_player_opposite(map, new_x, new_y);
	if (old_x != map->map_tile_x || old_y != map->map_tile_y)
		update_minimap(map, old_x, old_y);
}
