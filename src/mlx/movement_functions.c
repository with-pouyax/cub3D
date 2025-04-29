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
int	is_wall(char **map, double x, double y)
{
    int ix = (int)(x + PLAYER_WALL_BUFFER);
    int iy = (int)(y + PLAYER_WALL_BUFFER);

    // Check for out-of-bounds
    if (iy < 0 || ix < 0 || !map[iy] || ix >= (int)ft_strlen(map[iy]))
        return (1); // Treat out-of-bounds as wall

    // Check for wall or space
    if (map[iy][ix] == '1' || map[iy][ix] == ' ')
        return (1);

    ix = (int)(x - PLAYER_WALL_BUFFER);
    iy = (int)(y - PLAYER_WALL_BUFFER);

    if (iy < 0 || ix < 0 || !map[iy] || ix >= (int)ft_strlen(map[iy]))
        return (1);

    if (map[iy][ix] == '1' || map[iy][ix] == ' ')
        return (1);

    return (0);
}

void	move_player(t_file *map, double new_x, double new_y)
{
    double next_x;
    double next_y;

	next_x = map->player_x + new_x;
	next_y = map->player_y + new_y;
	if (!is_wall(map->game_map, next_x, map->player_y))
        map->player_x = next_x;
    if (!is_wall(map->game_map, map->player_x, next_y))
        map->player_y = next_y;
}

void	move_player_opposite(t_file *map, double new_x, double new_y)
{
	double next_x;
    double next_y;

	next_x = map->player_x - new_x;
	next_y = map->player_y - new_y;

	if (!is_wall(map->game_map, next_x, map->player_y))
        map->player_x = next_x;
    if (!is_wall(map->game_map, map->player_x, next_y))
		map->player_y = next_y;
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
