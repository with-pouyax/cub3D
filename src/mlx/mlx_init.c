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
	(*map)->mlx.mlx = NULL;
	(*map)->mlx.win = NULL;
	(*map)->mlx.img_ptr.img = NULL;
	(*map)->mlx.img_ptr.addr = NULL;
	(*map)->mlx.img_ptr.bits_per_pixel = 0;
	(*map)->mlx.img_ptr.line_length = 0;
	(*map)->mlx.img_ptr.endian = 0;
	return (0);
}

int	init_mlx(t_file **map)
{
	(*map)->mlx.mlx = mlx_init();
	if (!(*map)->mlx.mlx)
	{
		printf("[ERROR] Failed to initialize MiniLibX.\n");
		return (1);
	}
	return (0);
}

int	create_window(t_file **map)
{
	(*map)->mlx.win = mlx_new_window((*map)->mlx.mlx, WIDTH, HEIGHT, "Cub3D");
	if (!(*map)->mlx.win)
	{
		printf("[ERROR] Failed to create main image buffer.\n");
		return (1);
	}
	return (0);
}

int	create_image_buffer(t_file **map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		(*map)->image[i].img = mlx_xpm_file_to_image((*map)->mlx.mlx, 
					(*map)->image[i].path, &(*map)->image[i].w,  &(*map)->image[i].h);
		if(!(*map)->image[i].img)
		{
			printf("❌ Failed to load image %d from path: %s\n", i, (*map)->image[i].path);
			return (1);
		}
		i++;
	}
	(*map)->image[4].img = mlx_new_image((*map)->mlx.mlx, WIDTH, HEIGHT);
	if (!(*map)->image[4].img)
		return (1);
	i = 0;
	while (i < 5)
	{
		(*map)->image[i].addr = mlx_get_data_addr((*map)->image[i].img,
						&(*map)->image[i].bits_per_pixel, &(*map)->image[i].line_length,
						&(*map)->image[i].endian);
		if (!(*map)->image[i].addr)
		{
			printf("[ERROR] Failed to get main image buffer address.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	init_game_state(t_file **map)
{
	// (*map)->map_width = 1940;
	// (*map)->map_height = 1280;
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

int	assign_texture_paths_to_images(t_file *map)
{
	if (!map->textures.north || !map->textures.south ||
		!map->textures.west || !map->textures.east)
	{
		printf("❌ One or more texture paths are missing.\n");
		return (1);
	}
	map->image[0].path = ft_strdup(map->textures.north);
	map->image[1].path = ft_strdup(map->textures.south);
	map->image[2].path = ft_strdup(map->textures.west);
	map->image[3].path = ft_strdup(map->textures.east);
	if (!map->image[0].path || !map->image[1].path ||
		!map->image[2].path || !map->image[3].path)
	{
		printf("❌ Failed to duplicate one or more texture paths.\n");
		return (1);
	}
	return (0);
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
    init_game_state(map);
    if (init_mlx(map))
    {
        printf("[ERROR] Failed to initialize MLX.\n");
        return (1);
    }
    if (create_window(map))
    {
        printf("[ERROR] Failed to create window.\n");
        return (1);
    }
	if (assign_texture_paths_to_images(*map) != 0)
		return (1);
    if (create_image_buffer(map))
    {
        printf("[ERROR] Failed to create image buffer.\n");
        return (1);
    }
    if (init_minimap(map))
    {
        printf("[ERROR] Failed to initialize minimap.\n");
        return (1);
    }
    mlx_loop_hook((*map)->mlx.mlx, game_loop, map);
	if (set_event_hooks(map))
    {
        printf("[ERROR] Failed to set event hooks.\n");
        return (1);
    }
    mlx_loop((*map)->mlx.mlx);
    return (0);
}