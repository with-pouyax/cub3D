/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoushma <mhoushma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:27:25 by pghajard          #+#    #+#             */
/*   Updated: 2025/05/08 12:23:09 by mhoushma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//mlx_xpm_file_to_image--> to load the image from the file
int	load_image(t_file **map, int index)
{
	(*map)->image[index].img = mlx_xpm_file_to_image((*map)->mlx.mlx,
			(*map)->image[index].path, &(*map)->image[index].w,
			&(*map)->image[index].h);
	if (!(*map)->image[index].img)
	{
		printf("❌ Failed to load image\n");
		return (1);
	}
	if ((*map)->image[index].w < 32 || (*map)->image[index].h < 32)
	{
		printf("❌ Image at %s is too small (%dx%d)\n",
			(*map)->image[index].path, (*map)->image[index].w,
			(*map)->image[index].h);
		return (1);
	}
	if ((*map)->image[index].w > 1024 || (*map)->image[index].h > 1024)
	{
		printf("❌ Image at %s is too large (%dx%d)\n",
			(*map)->image[index].path, (*map)->image[index].w,
			(*map)->image[index].h);
		return (1);
	}
	return (0);
}

// mlx_get_data_addr--> to get the address of the image
// This address allows direct access to the image's pixel data, 
// enabling you to read or modify individual pixels. 
int	get_image_address(t_file **map, int index)
{
	(*map)->image[index].addr = mlx_get_data_addr((*map)->image[index].img,
			&(*map)->image[index].bits_per_pixel,
			&(*map)->image[index].line_length,
			&(*map)->image[index].endian);
	if (!(*map)->image[index].addr)
	{
		printf("[ERROR] Failed to get address for image at index %d\n", index);
		return (1);
	}
	return (0);
}

// here we initialize the player position and direction
// based on the map data
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

// This function assigns the texture paths to the image structures
// in the map structure. It duplicates the paths to ensure they are stored
int	assign_texture_paths_to_images(t_file *map)
{
	int	i;

	i = 0;
	if (!map->textures.north || !map->textures.south
		|| !map->textures.west || !map->textures.east)
		return (printf("❌ texture paths are missing.\n"), 1);
	map->image[0].path = ft_strdup(map->textures.north);
	map->image[1].path = ft_strdup(map->textures.south);
	map->image[2].path = ft_strdup(map->textures.west);
	map->image[3].path = ft_strdup(map->textures.east);
	if (!map->image[0].path || !map->image[1].path
		|| !map->image[2].path || !map->image[3].path)
	{
		while (i < 4)
		{
			if (map->image[i].path)
			{
				free(map->image[i].path);
				map->image[i].path = NULL;
			}
			i++;
		}
		return (printf("❌ Failed to dup texture_paths.\n"), 1);
	}
	return (0);
}

// Initialize MLX (MiniLibX), which is needed for rendering
// Create the window where everything will be rendered
// Create an image buffer to store and manipulate pixels before rendering
// TODO: Implement a function to create an image where you will draw the 
// game scene
// Set event hooks (keyboard, mouse, etc.)
// The game loop: This function will be called repeatedly to render frames
// mlx_loop_hook : game loop where you perform raycasting and draw the scene
// Start MLX loop (waits for events and continuously redraws the window)
int	start_game(t_file **map)
{
	init_game_state(map);
	if (init_mlx(map))
		return (1);
	if (create_window(map))
		return (1);
	if (assign_texture_paths_to_images(*map) != 0)
		return (1);
	if (create_image_buffer(map))
		return (1);
	if (init_minimap(map))
		return (1);
	if (set_event_hooks(map))
		return (1);
	mlx_loop_hook((*map)->mlx.mlx, game_loop, map);
	mlx_loop((*map)->mlx.mlx);
	return (0);
}
