/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_char_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoushma <mhoushma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:29:08 by pghajard          #+#    #+#             */
/*   Updated: 2025/05/06 13:12:08 by mhoushma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_player_count(int player_count)
{
	if (player_count == 0)
		return (ft_perror("no player", EINVAL), 1);
	return (0);
}

//*****************************************************************************
//*                                                                            
//* 1- we initialize the player count to 0
//* 2- we loop through the raw file
//* 3- we check if the current character is not a valid character and save 
//*    the position of the player
//* 4- also we check if there is a player in the map 
//*
//*****************************************************************************

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
			if (not_valid_char(raw_file[pos.i][pos.j],
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

	max_height = 100;
	max_width = 251;
	i = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > (size_t)max_width)
			return (1);
		i++;
	}
	if ((size_t)i > max_height)
		return (1);
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
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N' &&
				map[i][j] != 'S' && map[i][j] != 'E'
				&& map[i][j] != 'W' && map[i][j] != ' ')
				return (ft_perror("wrong map char", EINVAL), 1);
			j++;
		}
		i++;
	}
	return (0);
}

//*****************************************************************************
//*                                                                            
//* 1- in basic_map_check we check the validity of the map characters and if
//*    there is a player and no duplicate players and we save the position of
//*    the player
//* 2- in copy_map we copy the map to our game_map in the structure and also
//*    we get the max width of the map
//* 3- in wrong_ratio we check if the map is too wide or too high
//* 4- in wrong_map_char we check if the map contains only valid characters
//     =========> no TABS  <===============
//* 5- in check_walls we check if the walls are closed
//*****************************************************************************

int	not_map(t_file *map, int *index)
{
	if (basic_map_check(map, map->raw_file, index))
		return (1);
	if (copy_map(map, *index))
		return (ft_perror("problem copying map", ENOMEM), 1);
	map->player_y = map->player_y - *index;
	if (wrong_ratio(map->raw_file))
		return (ft_perror("wrong ratio", EINVAL), 1);
	if (wrong_map_char(map->game_map))
		return (ft_perror("wrong map char", EINVAL), 1);
	if (check_walls(map->game_map))
		return (ft_perror("wrong walls", EINVAL), 1);
	return (0);
}
