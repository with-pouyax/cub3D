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
        (*map)->player.left_rotate = true;
    else if (keycode == RIGHT)
        (*map)->player.right_rotate = true;
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
        (*map)->player.left_rotate = false;
    else if (keycode == RIGHT)
        (*map)->player.right_rotate = false;
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
    // mlx_loop((*map)->mlx.mlx);
	return (0);
}
// bool touch(float px, float py, t_file *game)
// {
//     int x = px / BLOCK;
//     int y = py / BLOCK;
//     if (game->game_map[y][x] == '1') // Assuming '1' represents a wall
//         return true;
//     return false;
// }


// bool touch(float px, float py, t_file *game)
// {
//     int x = px / BLOCK;
//     int y = py / BLOCK;

//     // printf("x = %d\n", x);
//     // printf("y = %d\n", y);
//     // Check if the tile is a wall
//     if (game->game_map[y][x] == '1') {
//         return true;
//     }
//     return false;
// }

// distance calculation functions
// float distance(float x, float y){
//     return sqrt(x * x + y * y);
// }

// float fixed_dist(float x1, float y1, float x2, float y2, t_file *game)
// {
//     float delta_x = x2 - x1;
//     float delta_y = y2 - y1;
//     float angle = atan2(delta_y, delta_x) - game->player.angle;
//     float fix_dist = distance(delta_x, delta_y) * cos(angle);
//     return fix_dist;
// }


// raycasting functions
// Change the type of the 'game' parameter in draw_line to 't_file *'
// void draw_line(t_player *player, t_file *game, float start_x, int i)
// {
//     float cos_angle = cos(start_x);
//     float sin_angle = sin(start_x);
//     float ray_x = player->x;
//     float ray_y = player->y;

//     while (!touch(ray_x, ray_y, game))  // Pass game (t_file *) here
//     {
//         if (DEBUG)
//             put_pixel(ray_x, ray_y, 0xFF0000, &game->mlx);  // Pass game (t_file *) here
//         ray_x += cos_angle;
//         ray_y += sin_angle;
//     }

//     if (!DEBUG)
//     {
//         float dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);  // Pass game (t_file *) here
//         float height = (BLOCK / dist) * (WIDTH / 2);
//         int start_y = (HEIGHT - height) / 2;
//         int end = start_y + height;
//         while (start_y < end)
//         {
//             put_pixel(i, start_y, 0x008000, &game->mlx);  // Pass game (t_file *) here
//             start_y++;
//         }
//     }
// }

void	img_pix_put(t_file *map, int x, int y, int color)
{
    char	*pixel;

    if (y < 0 || y >= map->map_height * TILE_SCALE
		|| x < 0 || x >= map->map_width * TILE_SCALE)
		return ;
    pixel = map->mlx.img_ptr.addr 
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

void    render_sky_floor(t_file **map)
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
            if(y < middle_of_screen)
                draw_sky_3d(map, x, y);
            else
                draw_floor_3d(map, x, y);
            y++;
        }
        x++;
    }
}

int game_loop(t_file **map)
{
    // printf("[DEBUG] Rendering sky and floor...\n");
    // render_sky_floor(map);

    // printf("[DEBUG] Performing raycasting...\n");
    // if (!recasting(map))
    // {
    //     printf("[ERROR] Raycasting failed.\n");
    //     return (1);
    // }

    // printf("[DEBUG] Putting main image to window...\n");
    // mlx_put_image_to_window(
    //     (*map)->mlx.mlx,
    //     (*map)->mlx.win,
    //     (*map)->mlx.img_ptr.img,
    //     0, 0);

    // printf("[DEBUG] Putting minimap image to window...\n");
    mlx_put_image_to_window(
        (*map)->mlx.mlx,
        (*map)->mlx.win,
        (*map)->minimap_img.img,
        10, 10);

    return (0);
}
