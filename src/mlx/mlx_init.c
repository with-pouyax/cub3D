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
