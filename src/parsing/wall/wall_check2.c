/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:30:13 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/13 15:30:14 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * Recursive flood fill function to check if map is enclosed by walls
 * @param map The map to check
 * @param row Current row position
 * @param col Current column position
 * @param found_edge Pointer to flag indicating if edge was found
 * @return void
 */
void	flood_fill(char **map, int row, int col, int *found_edge)
{
	if (!is_valid_for_fill(map, row, col, found_edge))
		return ;
	map[row][col] = 'X';
	flood_fill(map, row + 1, col, found_edge);
	flood_fill(map, row - 1, col, found_edge);
	flood_fill(map, row, col + 1, found_edge);
	flood_fill(map, row, col - 1, found_edge);
}

/**
 * Creates a backup of the map before flood fill
 * @param map The map to backup
 * @return A copy of the map or NULL if allocation fails
 */
char	**backup_map(char **map)
{
	char	**backup;
	int		i;

	i = 0;
	while (map[i])
		i++;
	backup = malloc(sizeof(char *) * (i + 1));
	if (!backup)
		return (NULL);
	i = 0;
	while (map[i])
	{
		backup[i] = ft_strdup(map[i]);
		if (!backup[i])
		{
			while (--i >= 0)
				free(backup[i]);
			free(backup);
			return (NULL);
		}
		i++;
	}
	backup[i] = NULL;
	return (backup);
}

/**
 * Restores the map from backup after flood fill
 * @param map The map to restore
 * @param backup The backup map
 * @return 0 on success, 1 on failure
 */
int	restore_from_backup(char **map, char **backup)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] && backup[i])
	{
		j = 0;
		while (map[i][j] && backup[i][j])
		{
			map[i][j] = backup[i][j];
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * Frees a map backup
 * @param backup The backup to free
 */
void	free_backup(char **backup)
{
	int	i;

	i = 0;
	while (backup[i])
		free(backup[i++]);
	free(backup);
} 