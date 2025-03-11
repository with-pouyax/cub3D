/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude <claude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-03-11 20:15:42 by claude            #+#    #+#             */
/*   Updated: 2023-03-11 20:15:42 by claude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Checks if a position is valid for flood fill
 * @param map The map to check
 * @param row The row to check
 * @param col The column to check
 * @return 1 if valid, 0 if not
 */
int	is_valid_position(char **map, int row, int col)
{
	if (row < 0 || col < 0)
		return (0);
	if (!map[row])
		return (0);
	if (!map[row][col])
		return (0);
	return (1);
}

/**
 * Checks if a character is a space or tab
 * @param c The character to check
 * @return 1 if space or tab, 0 if not
 */
int	is_space_or_tab(char c)
{
	return (c == ' ' || c == '\t');
}

/**
 * Checks if a character is a valid map character that can be filled
 * @param c The character to check
 * @return 1 if valid, 0 if not
 */
static int	is_fillable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/**
 * Checks if a position is at the edge of the map
 * @param map The map to check
 * @param row The row to check
 * @param col The column to check
 * @return 1 if at edge, 0 if not
 */
static int	is_at_edge(char **map, int row, int col)
{
	// Check if we're at the first or last row
	if (row == 0 || !map[row + 1])
		return (1);
	
	// Check if we're at the first or last column
	if (col == 0 || !map[row][col + 1])
		return (1);
	
	return (0);
}

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
	if (!is_valid_position(map, row, col))
	{
		*found_edge = 1;
		return ;
	}
	if (*found_edge)
		return ;
	if (map[row][col] == 'X')
		return ;
	if (map[row][col] == '1')
		return ;
	if (is_space_or_tab(map[row][col]))
	{
		*found_edge = 1;
		return ;
	}
	if (is_at_edge(map, row, col))
	{
		*found_edge = 1;
		return ;
	}
	
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
static char	**backup_map(char **map)
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
static int	restore_from_backup(char **map, char **backup)
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
static void	free_backup(char **backup)
{
	int	i;

	i = 0;
	while (backup[i])
		free(backup[i++]);
	free(backup);
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
	int		found_edge;
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
			if (is_fillable(map[i][j]))
			{
				found_edge = 0;
				flood_fill(map, i, j, &found_edge);
				if (found_edge)
				{
					free_backup(backup);
					return (1);
				}
				restore_from_backup(map, backup);
			}
			j++;
		}
		i++;
	}
	free_backup(backup);
	return (0);
}
