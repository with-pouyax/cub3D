/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_char_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:29:08 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/18 12:59:30 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	not_valid_char(char c, int *player_count, t_file *map, t_coord *pos)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		(*player_count)++;
		if (*player_count == 1)
		{
			map->player_dir = c;
			map->player_x = (*pos).j;
			map->player_y = (*pos).i;
		}
	}
	if (*player_count > 1)
		return (ft_perror("multiple players", EINVAL), 1);
	else if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && \
	c != 'W' && c != ' ' && c != '\t')
		return (ft_perror("invalid character", EINVAL), 1);
	return (0);
}

int	check_player_count(int player_count)
{
	if (player_count == 0)
		return (ft_perror("no player", EINVAL), 1);
	return (0);
}

int	basic_map_check(t_file *map, char **raw_file, int *index)
{
	t_coord	pos;
	int		player_count;

	pos.i = *index;
	player_count = 0;
	while (raw_file[pos.i])
	{
		pos.j = 0;
		while (raw_file[pos.i][pos.j])
		{
			if (not_valid_char(raw_file[pos.i][pos.j], \
			&player_count, map, &pos))
				return (1);
			pos.j++;
		}
		pos.i++;
	}
	if (check_player_count(player_count))
		return (1);
	return (0);
}

int	wrong_ratio(char **map)
{
	int			i;
	size_t		max_height;
	size_t		max_width;

	max_height = 50;
	max_width = 50;
	i = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > (size_t)max_width)
			return (ft_perror("wrong width", EINVAL), 1);
		i++;
	}
	if ((size_t)i > max_height)
		return (ft_perror("wrong height", EINVAL), 1);
	return (0);
}

int	wrong_map_char(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' \
			&& map[i][j] != 'N' && map[i][j] != 'S' \
			&& map[i][j] != 'E' && map[i][j] != 'W' \
			&& map[i][j] != ' ')
				return (ft_perror("wrong map char", EINVAL), 1);
			j++;
		}
		i++;
	}
	return (0);
}

int	not_map(t_file *map, int *index)
{
	if (basic_map_check(map, map->raw_file, index))
		return (ft_perror("basic map check", EINVAL), 1);
	if (copy_map(map, *index))
		return (ft_perror("copy map", EINVAL), 1);
	if (wrong_ratio(map->raw_file))
		return (ft_perror("wrong ratio", EINVAL), 1);
	if (wrong_map_char(map->game_map))
		return (ft_perror("wrong map char", EINVAL), 1);
	if (check_walls(map->game_map))
		return (ft_perror("wrong walls", EINVAL), 1);
	return (0);
}
