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

void    update_minimap(t_file *map, double old_x, double old_y)
{
    draw_square(map, (int)map->player_x, (int)map->player_y, COLOR_GREEN);
    if ((int)map->player_x != old_x)
        draw_square(map, old_x, old_y, COLOR_WHITE);
    if ((int)map->player_y != old_y)
        draw_square(map, old_x, old_y, COLOR_WHITE);
}

void    move_up_down(t_file *map, t_direction direction)
{
    double  old_x;
    double  old_y;
    double  new_x;
    double  new_y;


    old_x = (int)map->player_x;
    old_y = (int)map->player_y;
    new_x = map->dir_x_face * MOVE_SPEED;
    new_y = map->dir_y_face * MOVE_SPEED;
    printf("Initial Position: pos_x = %f, pos_y = %f\n",map->player_x,map->player_y);
    printf("Movement: next_x = %f, next_y = %f\n", new_x, new_y);

    if (direction == FORWARD)
    {
        if (map->game_map[(int)map->player_y][(int)(map->player_x + new_x)] != '1')
            map->player_x += new_x;
        if (map->game_map[(int)(map->player_y + new_y)][(int)map->player_x] != '1')
            map->player_y += new_y;
    }
    else if (direction == BACKWARD)
    {
        if (map->game_map[(int)map->player_y][(int)(map->player_x - new_x)] != '1')
            map->player_y += new_y;
        if (map->game_map[(int)(map->player_y - new_y)][(int)map->player_x] != '1')
            map->player_y -= new_y;
    }
    printf("Updated Position: pos_x = %f, pos_y = %f\n", map->player_x, map->player_y);
    if (old_x != map->map_tile_x || old_y != map->map_tile_y)
        update_minimap(map, old_x, old_y);
}

void    move_right_left(t_file *map, t_direction direction)
{
    double  old_x;
    double  old_y;
    double  new_x;
    double  new_y;

    old_x = (int)map->player_x;
    old_y = (int)map->player_y;
    new_x = map->plane_x * MOVE_SPEED;
    new_y = map->plane_y * MOVE_SPEED;
    if (direction == RIGHTWARD)
    {
        if (map->game_map[(int)map->player_y][(int)(map->player_x + new_x)] != '1')
            map->player_x += new_x;
        if (map->game_map[(int)(map->player_y + new_y)][(int)map->player_x] != '1')
            map->player_y += new_y;
    }
    else if (direction == LEFTWARD)
    {
        if (map->game_map[(int)map->player_y][(int)(map->player_x - new_x)] != '1')
            map->player_x -= new_x;
        if (map->game_map[(int)(map->player_y - new_y)][(int)map->player_x] != '1')
            map->player_y -= new_y;
    }

}

void move_forward(t_file *map)
{
    move_up_down(map, FORWARD);
}
void move_backward(t_file *map)
{
    move_up_down(map, BACKWARD);
}
void move_leftward(t_file *map)
{
    move_right_left(map, LEFTWARD);
}
void move_rightward(t_file *map)
{
    move_right_left(map, RIGHTWARD);
}
void rotate_left(t_file *map)
{
    double  rot_speed;
    double	tmp_dir_x;
    double	tmp_plane_x;

    tmp_dir_x = map->dir_x_face;
    tmp_plane_x = map->plane_x;
    rot_speed = 0.0;
    if (map->player_dir == 'N' || map->player_dir == 'S')
        rot_speed = -ROTATE_SPEED;
    else if (map->player_dir == 'E' || map->player_dir == 'W')
        rot_speed = ROTATE_SPEED;

    map->dir_x_face = map->dir_x_face * cos(rot_speed) - map->dir_y_face * sin(rot_speed);
    map->dir_y_face = tmp_dir_x * sin(rot_speed) + map->dir_y_face * cos(rot_speed);
    map->plane_x = map->plane_x * cos(rot_speed) - map->plane_y * sin(rot_speed);
    map->plane_y = tmp_plane_x * sin(rot_speed) + map->plane_y * cos(rot_speed);
}
void rotate_right(t_file *map)
{
    double  rot_speed;
    double	tmp_dir_x;
    double	tmp_plane_x;

    tmp_dir_x = map->dir_x_face;
    tmp_plane_x = map->plane_x;
    rot_speed = 0.0;
    if (map->player_dir == 'N' || map->player_dir == 'S')
        rot_speed = ROTATE_SPEED;
    else if (map->player_dir == 'E' || map->player_dir == 'W')
        rot_speed = -ROTATE_SPEED;

    map->dir_x_face = map->dir_x_face * cos(rot_speed) - map->dir_y_face * sin(rot_speed);
    map->dir_y_face = tmp_dir_x * sin(rot_speed) + map->dir_y_face * cos(rot_speed);
    map->plane_x = map->plane_x * cos(rot_speed) - map->plane_y * sin(rot_speed);
    map->plane_y = tmp_plane_x * sin(rot_speed) + map->plane_y * cos(rot_speed);
}

