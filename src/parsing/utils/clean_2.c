/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoushma <mhoushma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:29:57 by pghajard          #+#    #+#             */
/*   Updated: 2025/05/06 12:59:34 by mhoushma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	cleanup_mlx(t_file *map)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (map->image[i].img)
			mlx_destroy_image(map->mlx.mlx, map->image[i].img);
		i++;
	}
	if (map->mlx.img_ptr.img)
		mlx_destroy_image(map->mlx.mlx, map->mlx.img_ptr.img);
	if (map->mlx.win)
		mlx_destroy_window(map->mlx.mlx, map->mlx.win);
	if (map->mlx.mlx)
	{
		mlx_destroy_display(map->mlx.mlx);
		free(map->mlx.mlx);
	}
}
