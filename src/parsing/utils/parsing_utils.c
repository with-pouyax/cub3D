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
	print_whole_structure_in_order(*map);
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

void	check_header_elements(char *tmp, t_mapcheck *mc)
{
	if (tmp[mc->i] == 'N' && tmp[mc->i + 1] == 'O')
		mc->north = 1;
	else if (tmp[mc->i] == 'S' && tmp[mc->i + 1] == 'O')
		mc->south = 1;
	else if (tmp[mc->i] == 'W' && tmp[mc->i + 1] == 'E')
		mc->west = 1;
	else if (tmp[mc->i] == 'E' && tmp[mc->i + 1] == 'A')
		mc->east = 1;
	else if (tmp[mc->i] == 'F')
		mc->floor = 1;
	else if (tmp[mc->i] == 'C')
		mc->ceiling = 1;
}

void	detect_header_end_and_map_start(char *tmp, t_mapcheck *mc)
{
	if (mc->north && mc->south && mc->west && mc->east
		&& mc->floor && mc->ceiling && tmp[mc->i] == '\n')
		mc->header_done = 1;
	if (mc->header_done && tmp[mc->i] == '1')
		mc->map_started = 1;
}

int	check_empty_line_inside_map(char *tmp, t_mapcheck *mc)
{
	int j;

	if (tmp[mc->i] != '\n')
		return (0);
	j = mc->i + 1;
	while (tmp[j] == ' ')
		j++;
	if (tmp[j] == '\n')
	{
		while (tmp[j] == '\n' || tmp[j] == ' ')
			j++;
		if (tmp[j] == '1' || tmp[j] == '0')
			return (1);
	}
	return (0);
}

int	check_map_newlines(char *tmp)
{
	t_mapcheck mc;

	init_mapcheck(&mc);
	while (tmp[mc.i])
	{
		check_header_elements(tmp, &mc);
		detect_header_end_and_map_start(tmp, &mc);
		if (mc.map_started && check_empty_line_inside_map(tmp, &mc))
			return (1);
		mc.i++;
	}
	return (0);
}




int	parse_args(int ac, char **av, t_file **map)
{
	int		file_len;
	char	*tmp;

	(void)tmp;
	(void)av;
	(void)file_len;
	(void)map;
	if (arg_check(ac))
		return (1);
	if (extentions_check(av[1]))
		return (1);
	tmp = get_string(&file_len, av);
	if (check_map_newlines(tmp))
		return (free(tmp), ft_perror("newline between map lines", EINVAL), 1);
	(*map)->raw_file = ft_split(tmp, '\n');
	if (!(*map)->raw_file)
		return (free(tmp), ft_perror("malloc", errno), 1);
	trim_empty_lines(&((*map)->raw_file));
	if (parse_map(map))
		return (free(tmp), 1);
	free(tmp);
	return (0);
}
