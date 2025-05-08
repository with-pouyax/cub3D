/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recasting1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoushma <mhoushma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:27:25 by pghajard          #+#    #+#             */
/*   Updated: 2025/05/08 13:33:39 by mhoushma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//Determines whether the ray will step in a positive or negative direction in
//  both X and Y axes.
// It also calculates the initial distance to the first vertical or horizontal
//  grid boundary.
void	get_steps(t_file **map)
{
	if ((*map)->ray_dir_x < 0)
	{
		(*map)->ray_travel_x = -1;
		(*map)->dist_from_next_wall_x = ((*map)->player_x
				- (*map)->map_tile_x) * (*map)->distance_to_x;
	}
	else
	{
		(*map)->ray_travel_x = 1;
		(*map)->dist_from_next_wall_x = ((*map)->map_tile_x
				+ 1.0 - (*map)->player_x) * (*map)->distance_to_x;
	}
	if ((*map)->ray_dir_y < 0)
	{
		(*map)->ray_travel_y = -1;
		(*map)->dist_from_next_wall_y = ((*map)->player_y
				- (*map)->map_tile_y) * (*map)->distance_to_y;
	}
	else
	{
		(*map)->ray_travel_y = 1;
		(*map)->dist_from_next_wall_y = ((*map)->map_tile_y
				+ 1.0 - (*map)->player_y) * (*map)->distance_to_y;
	}
}

double	my_fabs(double x)
{
	if (x < 0)
	{
		return (-x);
	}
	else
	{
		return (x);
	}
}

//calculates how far the ray has to travel in X or Y direction to
//  go from one vertical or horizontal gridline to the next.
// for example : If the ray is perfectly vertical (ray_dir_x == 0), then
//  you’d never hit a vertical wall, we set the distance to the max.
// otherwise : compute how far we need to go in the X direction to move
//  exactly 1 cell horizontally on the map.
// fabs function -->to ensure the result is always positive

void	get_distance_to_next_cell(t_file **map)
{
	if ((*map)->ray_dir_x == 0)
		(*map)->distance_to_x = INT_MAX;
	else
		(*map)->distance_to_x = my_fabs(1 / (*map)->ray_dir_x);
	if ((*map)->ray_dir_y == 0)
		(*map)->distance_to_y = INT_MAX;
	else
		(*map)->distance_to_y = my_fabs(1 / (*map)->ray_dir_y);
	get_steps(map);
}

// جهت دقیق اشعه را تعیین می‌کند.
// it's preparing all the data you need to cast a single ray at column col 
// on the screen.
// ray_screen_pos --> where on the screen we are in relation
//  to the center of the screen.
// ray_screen_pos موقعیت پرتو در صفحه است (نسبت به وسط صفحه).
// ray_dir_x --> calculating the direction of the ray in the X and Y axes
//  based on the player's position and camera settings.
//map_tile _x --> places the player in a specific tile on the 2D grid.
//player_x -->is double, e.g., 4.53.
// By assigning it to map_tile_x (an int), we’re saying:
// “The player is currently inside tile 4 on the X-axis.”

void	setup_ray(t_file **map, int col)
{
	(*map)->map_tile_x = (*map)->player_x;
	(*map)->map_tile_y = (*map)->player_y;
	(*map)->ray_screen_pos = 2 * col / (double)WIDTH - 1;
	(*map)->ray_dir_x = (*map)->dir_x_face
		+ (*map)->plane_x * (*map)->ray_screen_pos;
	(*map)->ray_dir_y = (*map)->dir_y_face
		+ (*map)->plane_y * (*map)->ray_screen_pos;
}

//شبیه‌سازی پرتوهایی که از موقعیت بازیکن به سمت دنیای 
// بازی شلیک می‌شوند تا بررسی شود کجا به دیوار
//برخورد می‌کنند و بر اساس آن ستون‌هایی از دیوار روی صفحه نمایش داده می‌شود
/*it simulates rays being cast from the player's point of view into the
 2D map grid to detect walls and draw them on the screen*/
/*
loop over each column of pixels on the screen
initialize ray direction based on the camera plane
Casting a ray from the player into the world.
Determining what that ray hits (a wall, usually).
Calculating how far the wall is.
Drawing the wall column on screen based on that distance.
*/
int	recasting(t_file **map)
{
	int	col;

	col = 0;
	while (col < WIDTH)
	{
		setup_ray(map, col);
		get_distance_to_next_cell(map);
		dda_implimentation(map);
		calculate_perpwalldist(map);
		draw_col(*map, col);
		col++;
	}
	return (0);
}
