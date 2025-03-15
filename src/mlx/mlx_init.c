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
	(*map)->img_ptr.img = NULL;
	(*map)->img_ptr.addr = NULL;
	(*map)->img_ptr.bits_per_pixel = 0;
	(*map)->img_ptr.line_length = 0;
	(*map)->img_ptr.endian = 0;
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
	(*map)->mlx.win = mlx_new_window((*map)->mlx.mlx, 1000, 1000, "Cub3D");
	if (!(*map)->mlx.win)
		return (1);
	return (0);
}

int	create_image_buffer(t_file **map)
{
	(*map)->img_ptr.img = mlx_new_image((*map)->mlx.mlx, 1000, 1000); // mlx_new_image responsiblity is to create a new image buffer
	if (!(*map)->img_ptr.img)
		return (1);
	(*map)->img_ptr.addr = mlx_get_data_addr((*map)->img_ptr.img, &(*map)->img_ptr.bits_per_pixel, &(*map)->img_ptr.line_length, &(*map)->img_ptr.endian); // it is responsible for returning the address of the image buffer
	if (!(*map)->img_ptr.addr)
		return (1);
	
	return (0);
}

int	start_game(t_file **map)
{
	if (init_mlx(map))
		return (1);
	if (create_window(map))
		return (1);
	if (create_image_buffer(map))
		return (1);
	if (set_event_hooks(map))
		return (1);
	mlx_loop_hook((*map)->mlx.mlx, game_loop, map);
	mlx_loop((*map)->mlx.mlx);
	return (0);
} 