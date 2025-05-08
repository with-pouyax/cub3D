/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoushma <mhoushma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:27:25 by pghajard          #+#    #+#             */
/*   Updated: 2025/05/08 11:42:39 by mhoushma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//x, y: Coordinates of the pixel to draw.
// pixel --> This computes the memory address of the pixel to draw:
void	img_pix_put(t_file *map, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIDTH - 1 || y < 0 || y >= HEIGHT - 1)
		return ;
	pixel = map->image[4].addr
		+ (y * map->image[4].line_length + x
			* (map->image[4].bits_per_pixel / 8));
	*(int *)pixel = color;
}

void	draw_sky_3d(t_file **map, int x, int y)
{
	img_pix_put(*map, x, y, (*map)->colors.ceiling);
}

void	draw_floor_3d(t_file **map, int x, int y)
{
	img_pix_put(*map, x, y, (*map)->colors.floor);
}
