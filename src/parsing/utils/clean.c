/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:29:57 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/13 16:35:11 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	cleanup_mlx(t_file *map)
{
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

void	cleanup(t_file **map)
{
	if (!map || !*map)
		return ;
	cleanup_mlx(*map);
	clean_string_array(&((*map)->raw_file));
	clean_string_array(&((*map)->game_map));
	clean_texture_paths(&((*map)->textures));
	free(*map);
	*map = NULL;
}

void	clean_string_array(char ***array)
{
	int	i;

	if (!array || !*array)
		return ;
	i = 0;
	while ((*array)[i])
		free((*array)[i++]);
	free(*array);
	*array = NULL;
}

void	clean_texture_paths(t_texture_paths *textures)
{
	if (!textures)
		return ;
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->west)
		free(textures->west);
	if (textures->east)
		free(textures->east);
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
}
