/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:27:25 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/15 15:27:25 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
// Handler for X button (window close)
int	handle_esc_press(t_file **map)
{
	cleanup(map);
	exit(0);
	return (0);
}

// Handler for key press (ESC key)
int	handle_x_press(int keycode, t_file **map)
{
	if (keycode == 65307)
	{
		cleanup(map);
		exit(0);
	}
	return (0);
}

// Handle key press events
int	handle_keypress(int keycode, t_file **map)
{
	if (keycode == ESP)
		handle_esc_press(map);
    if (keycode == W)
        (*map)->player.key_up = true;
    else if (keycode == S)
        (*map)->player.key_down = true;
    else if (keycode == A)
        (*map)->player.key_left = true;
    else if (keycode == D)
        (*map)->player.key_right = true;
	else if (keycode == LEFT)
        (*map)->player.left_rotate = true;
    else if (keycode == RIGHT)
        (*map)->player.right_rotate = true;
    return (0);
}

int handle_keyrelease(int keycode, t_file **map)
{
    if (keycode == W)
        (*map)->player.key_up = false;
    else if (keycode == S)
        (*map)->player.key_down = false;
    else if (keycode == A)
        (*map)->player.key_left = false;
    else if (keycode == D)
        (*map)->player.key_right = false;
    else if (keycode == LEFT)
        (*map)->player.left_rotate = false;
    else if (keycode == RIGHT)
        (*map)->player.right_rotate = false;
    return (0);
}

int	set_event_hooks(t_file **map)
{
	printf("handle hooks before");

	mlx_key_hook((*map)->mlx.win, handle_x_press, map);
	mlx_hook((*map)->mlx.win, 2, 1L << 0, handle_keypress, map);
	mlx_hook((*map)->mlx.win, 3, 1L << 1, handle_keyrelease, map);
	mlx_hook((*map)->mlx.win, 17, 1L << 0, handle_esc_press, map);
	return (0);
}
