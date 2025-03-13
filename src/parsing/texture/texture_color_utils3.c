/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:29:41 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/13 15:29:42 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int process_color_line(t_file *map, char *line, t_color_flags *color_flags)
{
	int i;

	i = get_identifier_position(line);
	
	if (line[i] == 'F')
		return (process_floor_color(map, line + i, color_flags));
	else if (line[i] == 'C')
		return (process_ceiling_color(map, line + i, color_flags));
	return (0);
}

int check_all_elements_present(t_dir_flags *dir_flags, t_color_flags *color_flags)
{
	if (dir_flags->no != 1 || dir_flags->so != 1 || 
		dir_flags->we != 1 || dir_flags->ea != 1)
		return (ft_perror("missing texture direction", EINVAL), 1);
	if (color_flags->floor != 1 || color_flags->ceiling != 1)
		return (ft_perror("missing color", EINVAL), 1);
	return (0);
}

int process_line(t_file *map, char *line, t_parse_data *data)
{
	if (is_texture_line(line)) // if the line starts with NO, SO, WE, EA
	{
		if (process_texture_line(map, line, data->dir_flags)) // we process the line
			return (1);
		return (0);
	}
	else if (is_color_line(line)) // if the line starts with F or C
	{
		if (process_color_line(map, line, data->color_flags)) // we process color line
			return (1);
		return (0);
	}
	else // if the line is not a texture or color line
	{
		*(data->found_map_start) = 1;
		return (0);
	}
}

void init_parse_data(t_parse_data *data, t_dir_flags *dir_flags,
	t_color_flags *color_flags, int *found_map_start)
{
	*found_map_start = 0;
	data->dir_flags = dir_flags;
	data->color_flags = color_flags;
	data->found_map_start = found_map_start;
}

int process_current_line(t_file *map, int *index, t_parse_data *data)
{
	char *line;

	skip_empty_lines(map->raw_file, index);
	if (!map->raw_file[*index]) // if the line is empty, we return 0
		return (0);
	line = map->raw_file[*index];
	if (process_line(map, line, data)) //we process the line
		return (1);
	if (!*(data->found_map_start))
		(*index)++;
	return (0);
} 