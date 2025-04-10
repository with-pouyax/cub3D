/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:27:25 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/15 15:27:25 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

// Function to perform player rotation based on input
void perform_rotation(t_player *player)
{
    if (player->left_rotate)
        player->angle -= player->angle_speed;
    if (player->right_rotate)
        player->angle += player->angle_speed;
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;
}

// Function to move the player in the desired direction
void perform_move(t_player *player)
{
    // Calculate the cosine and sine of the player's angle for movement
    float cos_angle;
    float sin_angle;

    cos_angle  = cos(player->angle);
    sin_angle  = sin(player->angle);
    if (player->key_up)
    {
        player->x += cos_angle * player->speed;
        player->y += sin_angle * player->speed;
    }
    if (player->key_down)
    {
        player->x -= cos_angle * player->speed;
        player->y -= sin_angle * player->speed;
    }
    if (player->key_left)
    {
        player->x += sin_angle * player->speed;
        player->y -= cos_angle * player->speed;
    }
    if (player->key_right)
    {
        player->x -= sin_angle * player->speed;
        player->y += cos_angle * player->speed;
    }
}

void update_player_state(t_player *player)
{
    perform_rotation(player);
    perform_move(player);
}
