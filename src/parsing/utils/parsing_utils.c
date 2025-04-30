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
	if (!tmp)
		return (ft_perror("failed to read map file", errno), 1);
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
