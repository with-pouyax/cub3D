/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawings.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:27:25 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/15 15:27:25 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_color(t_file *map, int i)
{
	int		x;
	int		y;
	int		color;
	char	*pixel_address;

	x = map->texture_cordinat_x;
	y = map->texture_cordinat_y;
	pixel_address = map->image[i].addr
		+ (y * map->image[i].line_length)
		+ (x * (map->image[i].bits_per_pixel / 8));
	if (!map->image[i].addr)
	{
		printf("[ERROR] Texture %d not loaded properly. Address is NULL.\n", i);
		return (0);
	}
	if (!pixel_address)
	{
		printf("[ERROR] Invalid pixel address for texture %d\n", i);
		return (0);
	}
	color = *(int *)pixel_address;
	return (color);
}

// rendering the texture of the wall (or other objects) onto the screen
void	draw(t_file *map, int x, int texture)
{
	int	color;

	color = get_color(map, texture);
	img_pix_put(map, x, map->start_wall, color);
}

void	draw_column_pixels(t_file *map, int x)
{
	while (map->start_wall < map->end_wall)
	{
		map->texture_cordinat_y = (int)map->tex_position & (128 - 1);
		map->tex_position += map->step;
		if (map->hit_horizontal_wall == 1 && map->ray_dir_y < 0)
			draw(map, x, SOUTH);
		else if (map->hit_horizontal_wall == 1 && map->ray_dir_y > 0)
			draw(map, x, NORTH);
		else if (map->hit_vertical_wall == 1 && map->ray_dir_x < 0)
			draw(map, x, WEST);
		else if (map->hit_vertical_wall == 1 && map->ray_dir_x > 0)
			draw(map, x, EAST);
		map->start_wall++;
	}
}
