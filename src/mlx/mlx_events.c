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

void img_pix_put(t_file *map, int x, int y, int color)
{
    char *pixel;

    if (y < 0 || y >= map->map_height * TILE_SCALE || x < 0 || x >= map->map_width * TILE_SCALE)
    {
        printf("[DEBUG] img_pix_put: Out of bounds (x=%d, y=%d)\n", x, y);
        return ;
    }
    pixel = map->image[4].addr
        + (y * map->mlx.img_ptr.line_length + x * (map->mlx.img_ptr.bits_per_pixel / 8));
    *(int *)pixel = color;
}

void    draw_sky_3d(t_file **map, int x, int y)
{
    img_pix_put(*map, x, y, (*map)->colors.ceiling);
}

void    draw_floor_3d(t_file **map, int x, int y)
{
    img_pix_put(*map, x, y, (*map)->colors.floor);
}

//while (x ...)  --> This goes from the left to right side of the screen.
// while (y ...) --> This ensures every pixel on the screen is visited once.
// hight / 2 --> The screen is split in half horizontally:
// - If the pixel is in the top half, it is part of the sky.
// - Else, it is part of the floor.

void render_sky_floor(t_file **map)
{
    int x;
    int y;
    int middle_of_screen;


    x = 0;
    middle_of_screen = (*map)->map_height / 2;
    while (x < (*map)->map_width)
    {
        y = 0;
        while (y < (*map)->map_height)
        {
            if (y < middle_of_screen)
            {
                draw_sky_3d(map, x, y);
            }
            else
            {
                draw_floor_3d(map, x, y);
            }
            y++;
        }
        x++;
    }
}

int game_loop(t_file **map)
{
    // render_sky_floor(map);
    // if (recasting(map) != 0)
    // {
    //     printf("[ERROR] Raycasting failed.\n");
    //     return (1);
    // }

    mlx_put_image_to_window(
        (*map)->mlx.mlx,
        (*map)->mlx.win,
        (*map)->image[4].img,
        0, 0);

    mlx_put_image_to_window(
        (*map)->mlx.mlx,
        (*map)->mlx.win,
        (*map)->minimap_img.img,
        10, 10);

    return (0);
}
