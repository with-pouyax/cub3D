/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:27:25 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/15 15:27:25 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_map_mlx(t_file **map)
{
	// Initialize MLX members
	(*map)->mlx.mlx = NULL;
	(*map)->mlx.win = NULL;
	// Initialize IMG members
	(*map)->mlx.img_ptr.img = NULL;
	(*map)->mlx.img_ptr.addr = NULL;
	(*map)->mlx.img_ptr.bits_per_pixel = 0;
	(*map)->mlx.img_ptr.line_length = 0;
	(*map)->mlx.img_ptr.endian = 0;
	return (0);
}

int	init_mlx(t_file **map)
{
	(*map)->mlx.mlx = mlx_init(); // in failure, mlx_init returns NULL
	if (!(*map)->mlx.mlx)
		return (1);
	return (0);
}

int	create_window(t_file **map)
{
	(*map)->mlx.win = mlx_new_window((*map)->mlx.mlx, WIDTH, HEIGHT, "Cub3D");
	if (!(*map)->mlx.win)
		return (1);
	return (0);
}

int	create_image_buffer(t_file **map)
{
	
	(*map)->mlx.img_ptr.img  = mlx_new_image((*map)->mlx.mlx, WIDTH, HEIGHT); // mlx_new_image responsiblity is to create a new image buffer
	if (!(*map)->mlx.img_ptr.img)
		return (1);
	(*map)->mlx.img_ptr.addr = mlx_get_data_addr(
		(*map)->mlx.img_ptr.img,
		&(*map)->mlx.img_ptr.bits_per_pixel,
		&(*map)->mlx.img_ptr.line_length,
		&(*map)->mlx.img_ptr.endian); // it is responsible for returning the address of the image buffer
	if (!(*map)->mlx.img_ptr.addr)
		return (1);
	return (0);
}

void	init_game_state(t_file **map)
{
	if ((*map)->player_dir == 'N')
	{
		(*map)->plane_x = 0.66;
		(*map)->plane_y = 0;
	}
	else if ((*map)->player_dir == 'S')
	{
		(*map)->plane_x = -0.66;
		(*map)->plane_y = 0;
	}
	else if ((*map)->player_dir == 'W')
	{
		(*map)->plane_x = 0;
		(*map)->plane_y = 0.66;
	}
	else if ((*map)->player_dir == 'E')
	{
		(*map)->plane_x = 0;
		(*map)->plane_y = -0.66;
	}
}





// Initialize MLX (MiniLibX), which is needed for rendering
// Create the window where everything will be rendered
// Create an image buffer to store and manipulate pixels before rendering
// TODO: Implement a function to create an image where you will draw the game scene
// Set event hooks (keyboard, mouse, etc.)
// The game loop: This function will be called repeatedly to render frames
// mlx_loop_hook : game loop where you perform raycasting and draw the scene
// Start MLX loop (waits for events and continuously redraws the window)

int	start_game(t_file **map)
{
    printf("[DEBUG] Initializing game state...\n");
    init_game_state(map);

    printf("[DEBUG] Initializing MLX...\n");
    if (init_mlx(map))
    {
        printf("[ERROR] Failed to initialize MLX.\n");
        return (1);
    }

    printf("[DEBUG] Creating window...\n");
    if (create_window(map))
    {
        printf("[ERROR] Failed to create window.\n");
        return (1);
    }
    printf("[DEBUG] Creating image buffer...\n");
    if (create_image_buffer(map))
    {
        printf("[ERROR] Failed to create image buffer.\n");
        return (1);
    }
    printf("[DEBUG] Setting event hooks...\n");
    if (set_event_hooks(map))
    {
        printf("[ERROR] Failed to set event hooks.\n");
        return (1);
    }

    printf("[DEBUG] Initializing minimap...\n");
    if (init_minimap(map))
    {
        printf("[ERROR] Failed to initialize minimap.\n");
        return (1);
    }

    printf("[DEBUG] Starting game loop...\n");
    mlx_loop_hook((*map)->mlx.mlx, game_loop, map);
    mlx_loop((*map)->mlx.mlx);

    return (0);
}