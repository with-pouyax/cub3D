/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:30:01 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/13 16:39:08 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//*****************************************************************************
//*                                                                            
//* 1- using init_parse_data we setup our parse_data structure.
//* 2- we loop through the map file lines as long as we don't find the map 
//*    start.
//* 3- using process_current_line we process the current line.
//* 4- we go out of the loop when we find the map start.
//* 5- using check_all_elements_present we check if all the elements (N, S, W,
//*    E, F, C ) are present and are not duplicated.
//*****************************************************************************

int	parse_textures_and_colors(t_file *map, int *index, \
t_dir_flags *dir_flags, t_color_flags *color_flags)
{
	int				found_map_start;
	t_parse_data	data;

	init_parse_data(&data, dir_flags, color_flags, &found_map_start);
	while (map->raw_file[*index] && !found_map_start)
	{
		if (process_current_line(map, index, &data))
			return (1);
	}
	return (check_all_elements_present(dir_flags, color_flags));
}

//*****************************************************************************
//*                                                                            
//* 1- first we setup our two flags structures.
//* 2- using map_is_empty we check if the map is empty.
//* 3- using parse_textures_and_colors we parse the textures and colors.
//* 4- using not_map we check if the map is sourounded by walls.
//* 
//*****************************************************************************

int	parse_map(t_file **map)
{
	t_color_flags	color_flags;
	t_dir_flags		dir_flags;
	int				index;

	index = 0;
	dir_flags = (t_dir_flags){0, 0, 0, 0};
	color_flags = (t_color_flags){0, 0};
	if (map_is_empty((*map)->raw_file))
		return (1);
	if (parse_textures_and_colors(*map, &index, &dir_flags, &color_flags))
		return (1);
	if (not_map(*map, &index))
		return (1);
	return (0);
}

void	init_mapcheck(t_mapcheck *mc)
{
	mc->i = 0;
	mc->north = 0;
	mc->south = 0;
	mc->west = 0;
	mc->east = 0;
	mc->floor = 0;
	mc->ceiling = 0;
	mc->header_done = 0;
	mc->map_started = 0;
}
