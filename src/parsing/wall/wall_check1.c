/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:30:09 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/13 15:30:10 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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