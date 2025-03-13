/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:30:19 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/13 16:53:16 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * Checks a single position for wall integrity
 * @param map The map to check
 * @param backup The backup map
 * @param row The row to check
 * @param col The column to check
 * @return 1 if invalid (edge found), 0 if valid
 */
int	check_position(char **map, char **backup, int row, int col)
{
	int	found_edge;

	if (!is_fillable(map[row][col]))
		return (0);
	found_edge = 0;
	flood_fill(map, row, col, &found_edge);
	if (found_edge)
		return (1);
	restore_from_backup(map, backup);
	return (0);
}

/**
 * Checks if a map is surrounded by walls using flood fill
 * @param map The map to check
 * @return 0 if map is valid, 1 if not
 */
int	check_walls(char **map)
{
	int		i;
	int		j;
	char	**backup;

	backup = backup_map(map);
	if (!backup)
		return (1);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (check_position(map, backup, i, j))
			{
				free_backup(backup);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (free_backup(backup), 0);
}
