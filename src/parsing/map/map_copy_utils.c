/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_copy_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:29:16 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/13 15:29:17 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int get_map_height(char **map, int start_index)
{
	int	height;

	height = 0;
	while (map[start_index + height])
		height++;
	return (height);
}

char *ft_strdup_map(char *str)
{
	char	*dup;
	int		i;
	int		len;

	if (!str)
		return (NULL);
	
	// Find the length without trailing whitespace
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'))
		len--;
	
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (ft_perror("malloc", errno), NULL);
	
	i = 0;
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void free_game_map(char **game_map, int last_index)
{
	int	i;

	i = 0;
	while (i < last_index)
		free(game_map[i++]);
	free(game_map);
}

size_t update_max_width(char **map, int i, size_t max_width)
{
	size_t	current_width;

	current_width = ft_strlen(map[i]);
	if (current_width > max_width)
		return (current_width);
	return (max_width);
}

int copy_map_lines(t_file *map, int index, int height)
{
	int		i;
	size_t	max_width;

	i = 0;
	max_width = 0;
	while (i < height)
	{
		map->game_map[i] = ft_strdup_map(map->raw_file[index + i]);
		if (!map->game_map[i])
		{
			free_game_map(map->game_map, i);
			map->game_map = NULL;
			return (1);
		}
		max_width = update_max_width(map->game_map, i, max_width);
		i++;
	}
	map->game_map[i] = NULL;
	map->map_height = height;
	map->map_width = max_width;
	return (0);
}

int copy_map(t_file *map, int index)
{
	int	height;

	height = get_map_height(map->raw_file, index);
	map->game_map = malloc(sizeof(char *) * (height + 1));
	if (!map->game_map)
		return (ft_perror("malloc", errno), 1);
	if (copy_map_lines(map, index, height))
		return (1);
	return (0);
} 