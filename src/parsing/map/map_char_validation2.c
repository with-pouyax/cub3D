/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_copy_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:29:16 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/13 16:59:39 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_dir_face(t_file *map, char c)
{
	if (c == 'N')
	{
		map->dir_x_face = 0;
		map->dir_y_face = -1;
	}
	else if (c == 'S')
	{
		map->dir_x_face = 0;
		map->dir_y_face = 1;
	}
	else if (c == 'W')
	{
		map->dir_x_face = -1;
		map->dir_y_face = 0;
	}
	else if (c == 'E')
	{
		map->dir_x_face = 1;
		map->dir_y_face = 0;
	}
}

int	not_valid_char(char c, int *player_count, t_file *map, t_coord *pos)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		(*player_count)++;
		if (*player_count == 1)
		{
			map->player_dir = c;
			init_dir_face(map, c);
			map->player_x = (*pos).j + 0.5;
			map->player_y = (*pos).i - map->map_height + 0.5;
		}
	}
	if (*player_count > 1)
		return (ft_perror("multiple players", EINVAL), 1);
	else if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E'
		&& c != 'W' && c != ' ' && c != '\t')
		return (ft_perror("invalid character", EINVAL), 1);
	return (0);
}
