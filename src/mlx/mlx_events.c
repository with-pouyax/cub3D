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

//If you want smooth movement like this:
// Hold down W → move continuously forward

// Hold A + D → strafe

// Rotate while moving

// to reach this we set a flag (like key_up = true) during the key press...
// Then in the draw loop, which runs every frame (around 60 times per second), 
// we check those flags and move the player continuously if they're true.

// If we moved the player directly on key_press(), they would only move once per key tap,


// Handle key press events
int handle_keypress(int keycode, t_file **map)
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
        (*map)->player.key_left = true;
    else if (keycode == RIGHT)
        (*map)->player.key_right = true;
    return (0);
}

// Handle key release events
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
        (*map)->player.key_left = false;
    else if (keycode == RIGHT)
        (*map)->player.key_right = false;
    return (0);
}

//handle_keypress → Moves player when a key is pressed.
// handle_keyrelease → Stops movement when key is released.

// 🖼 mlx_loop_hook(game.mlx, draw_loop, &game);
// This sets a function (draw_loop) to be called on every iteration of the main loop.
// This is where the actual rendering happens — player movement, map redraws, etc.
// &game gets passed into draw_loop(), giving you access to everything: player, map, images, etc.

// mlx_loop runs forever:
// On key press → key_press() is called
// On key release → key_release() is called
// On each frame → draw_loop() is called
int	set_event_hooks(t_file **map)
{
	mlx_key_hook((*map)->mlx.win, handle_x_press, map);
	mlx_hook((*map)->mlx.win, 2, 1L << 0, handle_keypress, map);
    mlx_hook((*map)->mlx.win, 3, 1L << 1, handle_keyrelease, map);
	mlx_hook((*map)->mlx.win, 17, 0, handle_esc_press, map);
    mlx_loop((*map)->mlx.mlx);
	return (0);
}

int	game_loop(t_file **map)
{
    t_player    *player = &(*map)->player;
    
    update_player_state(player);
    mlx_clear_window((*map)->mlx.mlx, (*map)->mlx.win);
    clean_img(&(*map)->mlx); 
	draw_square(WIDTH / 2, HEIGHT / 2, 10,  0x00FF00, &(*map)->mlx);

	// TODO: Implement raycasting here to draw the game scene
    // Display the image to the window
    mlx_put_image_to_window((*map)->mlx.mlx, (*map)->mlx.win, (*map)->mlx.img_ptr.img, 0, 0);
	return(0);
}