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
int	is_fillable(char c)
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
int	is_at_edge(char **map, int row, int col)
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
 * Checks if the current position is valid for flood filling
 * @param map The map to check
 * @param row Current row position
 * @param col Current column position
 * @param found_edge Pointer to flag indicating if edge was found
 * @return 1 if position is valid for filling, 0 if not
 */
int	is_valid_for_fill(char **map, int row, int col, int *found_edge)
{
	if (!is_valid_position(map, row, col))
	{
		*found_edge = 1;
		return (0);
	}
	if (*found_edge)
		return (0);
	if (map[row][col] == 'X')
		return (0);
	if (map[row][col] == '1')
		return (0);
	if (is_space_or_tab(map[row][col]))
	{
		*found_edge = 1;
		return (0);
	}
	if (is_at_edge(map, row, col))
	{
		*found_edge = 1;
		return (0);
	}
	return (1);
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
