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
    map->player.x = 2.0;  // Example: Start at grid position (2,2)
    map->player.y = 2.0;

    map->player.dir_x = -1.0; // Facing left (-X direction)
    map->player.dir_y = 0.0;  // No movement in Y direction

    map->player.plane_x = 0.0;  // No tilt in X
    map->player.plane_y = 0.66; // Camera plane for FOV (adjustable)
}