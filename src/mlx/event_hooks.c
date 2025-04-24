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
		move_forward(*map);
	else if (keycode == S)
		move_backward(*map);
	else if (keycode == A)
		move_leftward(*map);
	else if (keycode == D)
		move_rightward(*map);
	else if (keycode == LEFT)
		rotate_left(*map);
	else if (keycode == RIGHT)
		rotate_right(*map);
	return (0);
}

int	set_event_hooks(t_file **map)
{
	mlx_key_hook((*map)->mlx.win, handle_x_press, map);
	mlx_hook((*map)->mlx.win, 2, 1L << 0, handle_keypress, map);
	mlx_hook((*map)->mlx.win, 17, 1L << 0, handle_esc_press, map);
	return (0);
}
