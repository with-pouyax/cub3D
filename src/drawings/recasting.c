/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recasting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:27:25 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/15 15:27:25 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_color(t_file *map, int i)
{
    int x;
    int y;

    x = map->texture_cordinat_x;
    y = map->texture_cordinat_y;
	return (*(int *)(map->image[i].addr
        + (y * map->image[i].line_length + x * (map->image[i].bits_per_pixel / 8))));
}
// rendering the texture of the wall (or other objects) onto the screen
void	draw(t_file *map, int x, int texture)
{
	int	color;

	color = get_color(map, texture);
	img_pix_put(map, x, map->start_wall, color);
}

void draw_column_pixels(t_file *map, int x)
{
    while (map->start_wall < map->end_wall)
    {
        map->texture_cordinat_y = (int)map->tex_position & (128 - 1);  // Calculate texture y-coordinate
        map->tex_position += map->step;  // Move along the texture

        // Determine which side of the wall the ray hit and draw accordingly
        if (map->hit_vertical_wall == 1 && map->ray_dir_y < 0)
            draw(map, x, SOUTH);  // South side
        else if (map->hit_vertical_wall == 1 && map->ray_dir_y > 0)
            draw(map, x, NORTH);  // North side
        else if (map->hit_vertical_wall == 0 && map->ray_dir_x < 0)
            draw(map, x, WEST);   // West side
        else if (map->hit_vertical_wall == 0 && map->ray_dir_x > 0)
            draw(map, x, EAST);   // East side

        map->start_wall++;  // Move to the next pixel in the column
    }
}

double get_fractional_part(double wall_pos)
{
    return (wall_pos - floor(wall_pos));
}
//  // Maps fractional position to texture width
int map_hit_to_texture_x(double wall_x)
{
    return (int)(wall_x * 128);  // Maps fractional position to texture width
}

int flip_texture_if_needed(t_file *map, int tex_x)
{
    if (map->hit_vertical_wall == 1 && map->ray_dir_x > 0)
        tex_x = 128 - tex_x - 1;  // Flip for East-facing walls
    else if (map->hit_vertical_wall == 1 && map->ray_dir_y < 0)
        tex_x = 128 - tex_x - 1;  // Flip for North-facing walls
    return (tex_x);
}
//is the exact position (decimal) where the ray hit the wall on the face of 
// the wall tile, from 0.0 to 1.0.

void    texture_definition(t_file *map, int wall_hight)
{
    if(map->hit_vertical_wall == 1)
        map->pos_hit_wall_x = map->plane_y + map->perpendicular_wall_distance * map->ray_dir_y;
    else if (map->hit_vertical_wall == 1)
        map->pos_hit_wall_x = map->plane_x + map->perpendicular_wall_distance * map->ray_dir_x;
    map->pos_hit_wall_x = get_fractional_part(map->pos_hit_wall_x);
    map->texture_cordinat_x = map_hit_to_texture_x(map->pos_hit_wall_x);
    map->texture_cordinat_x = flip_texture_if_needed(map, map->texture_cordinat_x);
    map->step = 1.0 * 128 / wall_hight;
    map->texture_cordinat_x = (map->start_wall - map->map_height / 2 + wall_hight / 2) * map->step;

}

void    calculate_wall_hight(t_file *map, int *wall_height)
{
    *wall_height = map->map_height / map->perpendicular_wall_distance;
    map->start_wall = -*wall_height / 2 + map->map_height / 2;
    if (map->start_wall < 0)
        map->start_wall = 0;
    map->end_wall = *wall_height / 2 + map->map_height / 2;
    if (map->end_wall >= map->map_height)
        map->end_wall = map->map_height - 1;
}

//calculate_wall_hight : calculates how tall the wall slice should appear on screen
//figuring out which part of the wall texture to draw.
//Draw each pixel of the column
//Choose correct wall texture
void    draw_col(t_file *map, int x)
{
    int wall_height;

    calculate_wall_hight(map, &wall_height);
    texture_definition(map, wall_height);
    draw_column_pixels(map, x);
}

void calculate_perpwalldist(t_file **map)
{
    if ((*map)->hit_vertical_wall == 1)
        (*map)->perpendicular_wall_distance = ((*map)->dist_from_next_wall_x - (*map)->distance_to_x);
    else
        (*map)->perpendicular_wall_distance = ((*map)->dist_from_next_wall_y - (*map)->distance_to_y);
}

//ray will continue to step through the grid cells until it hits wall (== 1)
void    DDA_implimentation(t_file **map)
{
    int hit_wall;

    hit_wall = 0;
    while (hit_wall == 0)
    {
        if((*map)->dist_from_next_wall_x < (*map)->dist_from_next_wall_y)
        {
            (*map)->dist_from_next_wall_x += (*map)->distance_to_x;
            (*map)->map_tile_x += (*map)->ray_travel_x;
            (*map)->hit_vertical_wall = 1;
            (*map)->hit_horizontal_wall = 0;
        }
        else
        {
            (*map)->dist_from_next_wall_y += (*map)->distance_to_y;
            (*map)->map_tile_y += (*map)->ray_travel_y;
            (*map)->hit_vertical_wall = 0;
            (*map)->hit_horizontal_wall = 1;
        }
        if ((*map)->game_map[(*map)->map_tile_y][(*map)->map_tile_x] == '1')
        {
            hit_wall = 1;
            calculate_perpwalldist(map);
        }
    }
}

//how far ray travels in the x and y directions (step_x, step_y)
// how far the ray is from the next wall in each direction (side_dist_x, side_dist_y).
//dist_from_next_wall_x : The distance to the next vertical grid boundary (left|right).
// dist_from_next_wall_y :  The distance to the next horizontal grid boundary (up|down).
// If side_dist_x is smaller than side_dist_y, it means the ray will hit a 
// vertical grid line first, so we update the x coordinate.
void    get_steps(t_file **map)
{
    if ((*map)->ray_dir_x < 0)
    {
        (*map)->ray_travel_x = -1;
        (*map)->dist_from_next_wall_x = ((*map)->player_x - (*map)->map_tile_x) * (*map)->distance_to_x;
    }
    else
    {
        (*map)->ray_travel_x = 1;
        (*map)->dist_from_next_wall_x = ((*map)->map_tile_x + 1.0 - (*map)->player_x) * (*map)->distance_to_x;
    }
    if ((*map)->ray_dir_y < 0)
    {
        (*map)->ray_travel_y = -1;
        (*map)->dist_from_next_wall_y = ((*map)->player_y - (*map)->map_tile_y) * (*map)->distance_to_y;
    }
    else
    {
        (*map)->ray_travel_x = 1;
        (*map)->dist_from_next_wall_x = ((*map)->map_tile_y + 1.0 - (*map)->player_y) * (*map)->distance_to_y;
    }
}

double  my_fabs(double x)
{
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}

//his function calculates how far the ray has to travel in X or Y direction to
//  go from one vertical or horizontal gridline to the next.
// for example : If the ray is perfectly vertical (ray_dir_x == 0), then
//  you’d never hit a vertical wall, we set the distance to the max.
// otherwise : compute how far we need to go in the X direction to move
//  exactly 1 cell horizontally on the map.
// fabs function -->to ensure the result is always positive

void    get_distance_to_next_cell(t_file **map)
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

// it's preparing all the data you need to cast a single ray at column col 
// on the screen.
// ray_screen_pos --> is telling us where on the screen we are in relation
//  to the center of the screen.
// ray_dir_x --> calculating the direction of the ray in the X and Y axes
//  based on the player's position and camera settings.
void    setup_ray(t_file **map, int col)
{
    (*map)->map_tile_x = (*map)->player_x;
    (*map)->map_tile_y = (*map)->player_y;
    (*map)->ray_screen_pos = 2 * col / (double)(*map)->map_width - 1;
    (*map)->ray_dir_x = (*map)->dir_x_face  + (*map)->plane_x * (*map)->ray_screen_pos;
    (*map)->ray_dir_y = (*map)->dir_y_face  + (*map)->plane_y * (*map)->ray_screen_pos;
}

/*
loop over each column of pixels on the screen
initialize ray direction based on the camera plane
Casting a ray from the player into the world.
Determining what that ray hits (a wall, usually).
Calculating how far the wall is.
Drawing the wall column on screen based on that distance.
*/
int recasting(t_file **map)
{
    int col;

    col = 0;
    while (col < (*map)->map_width)
    {
        printf("[DEBUG] Processing column: %d\n", col);
        setup_ray(map, col);
        printf("[DEBUG] Ray direction: (x: %f, y: %f)\n", (*map)->ray_dir_x, (*map)->ray_dir_y);
        get_distance_to_next_cell(map);
        DDA_implimentation(map);
        printf("[DEBUG] Wall hit at tile: (x: %d, y: %d)\n", (*map)->map_tile_x, (*map)->map_tile_y);
        printf("[DEBUG] Perpendicular wall distance: %f\n", (*map)->perpendicular_wall_distance);
        draw_col(*map, col);
        printf("[DEBUG] Finished drawing column: %d\n", col);
        col++;
    }
    return (0);
}
