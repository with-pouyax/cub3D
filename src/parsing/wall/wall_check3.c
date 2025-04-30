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

//*****************************************************************************
//*                                                                            
//* 1- using is_fillable we check if the current character is fillable
//* 2- using flood_fill we see if we can reach out of the map and
//*    if yes we return 1
//* 3- if we can't reach out of the map we restore the map from the backup
//* 4- if we can't reach out of the map we return 0
//*****************************************************************************

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

//*****************************************************************************
//*                                                                            
//* 1- we first backup the map
//* 2- we loop through the map characters by characters
//* 3- using check_position we check if the current position is a valid 
//*    position and if we can reach out of the map
//* 4- if we can't reach out of the map we free the backup and return 0
//*
//*****************************************************************************

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
