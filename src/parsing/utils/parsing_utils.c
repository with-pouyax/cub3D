/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:30:01 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/13 15:30:02 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int parse_textures_and_colors(t_file *map, int *index, 
	t_dir_flags *dir_flags, t_color_flags *color_flags)
{
	int found_map_start;
	t_parse_data data;

	init_parse_data(&data, dir_flags, color_flags, &found_map_start);
	
	while (map->raw_file[*index] && !found_map_start)
	{
		if (process_current_line(map, index, &data))
			return (1);
	}
	
	return (check_all_elements_present(dir_flags, color_flags));
}

int parse_map(t_file **map)
{
    int index;
    t_dir_flags dir_flags;
    t_color_flags color_flags;

    index = 0;
    dir_flags = (t_dir_flags){0, 0, 0, 0};
    color_flags = (t_color_flags){0, 0};
    
    if(map_is_empty((*map)->raw_file))
        return (1);
    if (parse_textures_and_colors(*map, &index, &dir_flags, &color_flags))
        return (1);
    if (not_map(*map, &index))
        return (1);
    
    print_whole_structure_in_order(*map);
    return (0);
}

int parse_args(int ac, char **av, t_file **map)
{
	int file_len;
	char *tmp;

	(void)tmp;
	(void)av;
	(void)file_len;
	(void)map;
	if (arg_check(ac))
		return (1);
	if(extentions_check(av[1]))
		 return (1);
	tmp = get_string(&file_len, av);
	(*map)->raw_file = ft_split(tmp, '\n');
	if (!(*map)->raw_file)
		return (free(tmp), ft_perror("malloc", errno), 1);
	trim_empty_lines(&((*map)->raw_file)); // we trim the empty lines at the end of the map->raw_file 
	if (parse_map(map))
		return (free(tmp), 1);
	free(tmp);
	return (0);
} 