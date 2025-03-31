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

void rotate_left(t_file **map)
{
    double old_dir_x = (*map)->player.dir_x;
    (*map)->player.dir_x = (*map)->player.dir_x * cos(-ROTATE_SPEED) - (*map)->player.dir_y * sin(-ROTATE_SPEED);
    (*map)->player.dir_y = old_dir_x * sin(-ROTATE_SPEED) + (*map)->player.dir_y * cos(-ROTATE_SPEED);
}

void rotate_right(t_file **map)
{
    double old_dir_x = (*map)->player.dir_x;
    (*map)->player.dir_x = (*map)->player.dir_x * cos(ROTATE_SPEED) - (*map)->player.dir_y * sin(ROTATE_SPEED);
    (*map)->player.dir_y = old_dir_x * sin(ROTATE_SPEED) + (*map)->player.dir_y * cos(ROTATE_SPEED);
}