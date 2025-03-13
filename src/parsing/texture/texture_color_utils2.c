/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:29:36 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/13 16:29:54 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	process_we_texture(t_file *map, char *line, t_dir_flags *dir_flags)
{
	dir_flags->we++;
	if (dir_flags->we > 1)
		return (ft_perror("duplicate WE texture", EINVAL), 1);
	if (extract_and_assign_path(line, &map->textures.west))
		return (1);
	return (0);
}

int	process_ea_texture(t_file *map, char *line, t_dir_flags *dir_flags)
{
	dir_flags->ea++;
	if (dir_flags->ea > 1)
		return (ft_perror("duplicate EA texture", EINVAL), 1);
	if (extract_and_assign_path(line, &map->textures.east))
		return (1);
	return (0);
}

int	process_texture_line(t_file *map, char *line, t_dir_flags *dir_flags)
{
	int	i;

	i = get_identifier_position(line);
	if (line[i] == 'N' && line[i + 1] == 'O')
		return (process_no_texture(map, line + i, dir_flags));
	else if (line[i] == 'S' && line[i + 1] == 'O')
		return (process_so_texture(map, line + i, dir_flags));
	else if (line[i] == 'W' && line[i + 1] == 'E')
		return (process_we_texture(map, line + i, dir_flags));
	else if (line[i] == 'E' && line[i + 1] == 'A')
		return (process_ea_texture(map, line + i, dir_flags));
	return (0);
}

int	process_floor_color(t_file *map, char *line, t_color_flags *color_flags)
{
	color_flags->floor++;
	if (color_flags->floor > 1)
		return (ft_perror("duplicate floor color", EINVAL), 1);
	if (extract_rgb(line, &map->colors.floor))
		return (ft_perror("invalid floor RGB format", EINVAL), 1);
	return (0);
}

int	process_ceiling_color(t_file *map, char *line, t_color_flags *color_flags)
{
	color_flags->ceiling++;
	if (color_flags->ceiling > 1)
		return (ft_perror("duplicate ceiling color", EINVAL), 1);
	if (extract_rgb(line, &map->colors.ceiling))
		return (ft_perror("invalid ceiling RGB format", EINVAL), 1);
	return (0);
}
