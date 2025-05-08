/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoushma <mhoushma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:27:25 by pghajard          #+#    #+#             */
/*   Updated: 2025/05/08 10:53:23 by mhoushma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//*****************************************************************************
//*                                                                            
//* 1- we initialize the mlx and the window related variables                 *
//*****************************************************************************
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

//here we create the image buffer and load the textures
//mlx_new_image--> to create a new image
//The number 4 corresponds to the four directions
//The fifth image (map->image[4]) is created to act as a blank canvas 
//where the game will draw everything the player sees
int	create_image_buffer(t_file **map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (load_image(map, i))
			return (1);
		i++;
	}
	(*map)->image[4].img = mlx_new_image((*map)->mlx.mlx, WIDTH, HEIGHT);
	if (!(*map)->image[4].img)
		return (1);
	i = 0;
	while (i < 5)
	{
		if (get_image_address(map, i))
			return (1);
		i++;
	}
	return (0);
}
