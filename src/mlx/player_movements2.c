/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:27:25 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/15 15:27:25 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

void	rotate_left(t_file *map)
{
	double	rot_speed;
	double	tmp_dir_x;
	double	tmp_plane_x;

	tmp_dir_x = map->dir_x_face;
	tmp_plane_x = map->plane_x;
	rot_speed = 0.0;
	if (map->player_dir == 'N' || map->player_dir == 'S')
		rot_speed = -ROTATE_SPEED;
	else if (map->player_dir == 'E' || map->player_dir == 'W')
		rot_speed = ROTATE_SPEED;
	map->dir_x_face = map->dir_x_face * cos(rot_speed)
		- map->dir_y_face * sin(rot_speed);
	map->dir_y_face = tmp_dir_x * sin(rot_speed)
		+ map->dir_y_face * cos(rot_speed);
	map->plane_x = map->plane_x * cos(rot_speed)
		- map->plane_y * sin(rot_speed);
	map->plane_y = tmp_plane_x * sin(rot_speed)
		+ map->plane_y * cos(rot_speed);
}

void	rotate_right(t_file *map)
{
	double	rot_speed;
	double	tmp_dir_x;
	double	tmp_plane_x;

	tmp_dir_x = map->dir_x_face;
	tmp_plane_x = map->plane_x;
	rot_speed = 0.0;
	if (map->player_dir == 'N' || map->player_dir == 'S')
		rot_speed = ROTATE_SPEED;
	else if (map->player_dir == 'E' || map->player_dir == 'W')
		rot_speed = -ROTATE_SPEED;
	map->dir_x_face = map->dir_x_face * cos(rot_speed)
		- map->dir_y_face * sin(rot_speed);
	map->dir_y_face = tmp_dir_x * sin(rot_speed)
		+ map->dir_y_face * cos(rot_speed);
	map->plane_x = map->plane_x * cos(rot_speed)
		- map->plane_y * sin(rot_speed);
	map->plane_y = tmp_plane_x * sin(rot_speed)
		+ map->plane_y * cos(rot_speed);
}
