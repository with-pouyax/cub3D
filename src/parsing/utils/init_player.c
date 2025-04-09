/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:29:57 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/13 16:35:11 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//Direction (dir_x, dir_y) → Controls movement direction:

// (-1,0) → Facing left

// (1,0) → Facing right

// (0,-1) → Facing up

// (0,1) → Facing down

// Other values allow diagonal directions.
void init_player(t_file *map)
{
    map->player.x = WIDTH / 2;  // Example: Start at grid position (2,2)
    map->player.y = HEIGHT / 2;

    map->player.key_up = false;
    map->player.key_down = false;
    map->player.key_left = false;
    map->player.key_right = false;
    map->player.left_rotate = false;
    map->player.right_rotate = false;
    map->player.speed = 3;
    map->player.angle_speed = 0.03;
}