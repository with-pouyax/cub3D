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
int	handle_x_press(int keycode, t_file *map)
{
	if (keycode == 65307)
	{
		cleanup(&map);
		exit(0);
	}
	return (0);
}

// Handle key press events
int handle_keypress(int keycode, t_file **map)
{
    if (keycode == 65307) // ESC key
        handle_esc_press(map);
    else if (keycode == 119) // W key (Move forward)
        move_forward(map);
    else if (keycode == 115) // S key (Move backward)
        move_backward(map);
    else if (keycode == 97) // A key (Move left)
        move_left(map);
    else if (keycode == 100) // D key (Move right)
        move_right(map);
	else if (keycode == 65361) // Left arrow key (Look left)
        rotate_left(map);
    else if (keycode == 65363) // Right arrow key (Look right)
        rotate_right(map);
    return (0);
}

// Handle key release events
int handle_keyrelease(int keycode, t_file **map)
{
    (void)keycode;
    (void)map;
    return (0);
}
//handle_keypress → Moves player when a key is pressed.
// handle_keyrelease → Stops movement when key is released.
int	set_event_hooks(t_file **map)
{
	// Hook for ESC key
	mlx_key_hook((*map)->mlx.win, handle_x_press, *map);

	mlx_hook((*map)->mlx.win, 2, 1L<<0, handle_keypress, map); // Key press
    mlx_hook((*map)->mlx.win, 3, 1L<<1, handle_keyrelease, map); // Key release
	// Hook for window close button (X)
	mlx_hook((*map)->mlx.win, 17, 0, handle_esc_press, *map);

	return (0);
}

int	game_loop(t_file **map)
{
	(void)map;
	
	// TODO: Implement raycasting here to draw the game scene
    
    // Display the image to the window
    mlx_put_image_to_window((*map)->mlx.mlx, (*map)->mlx.win, (*map)->img_ptr.img, 0, 0);
	return(0);
}