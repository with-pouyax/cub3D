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
int	handle_esc_press(t_file *map)
{
	cleanup(&map);
	exit(0);
	return (0);
}

// Handler for key press (ESC key)
int	handle_x_press(int keycode, t_file *map)
{
	if (keycode == 65307) // ESC key code
	{
		cleanup(&map);
		exit(0);
	}
	return (0);
}

int	set_event_hooks(t_file **map)
{
	// Hook for ESC key
	mlx_key_hook((*map)->mlx.win, handle_x_press, *map);

	// Hook for window close button (X)
	mlx_hook((*map)->mlx.win, 17, 0, handle_esc_press, *map);

	return (0);
}

int	game_loop(t_file **map)
{
	(void)map;
	
	return (0);
} 