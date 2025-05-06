/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoushma <mhoushma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:30:01 by pghajard          #+#    #+#             */
/*   Updated: 2025/05/06 13:23:03 by mhoushma         ###   ########.fr       */
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

//*****************************************************************************
//*                                                                            
//* 1- if the current character is not a newline we return 0
//* 2- otherwise we save the index of the next character in j variable
//* 3- we loop through the next characters as long as they are spaces
//* 4- if we find a newline we skip the next characters as long as they are
//*    newlines or spaces
//* 5- if we find a 1 or 0 we return 1
//* 6- otherwise we return 0
//* ****************************************************************************

int	check_empty_line_inside_map(char *tmp, t_mapcheck *mc)
{
	int	j;

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

//*****************************************************************************
//*                                                                            
//* 1- we initialize the mapcheck structure
//* 2- we loop through the map file characters
//* 3- using check_header_elements we set the N, S, W, E, F, C flags to 1 if
//*    we find the corresponding characters in the map file
//* 4- using detect_header_end_and_map_start we set the header_done if we find
//*    enter after the header elements and we set the map_started if we find
//*    a 1 after the header elements and a newline.
//* 5- if the map_started is 1 and we find a newline inside the map we return 1
//* 
//*****************************************************************************

int	check_map_newlines(char *tmp)
{
	t_mapcheck	mc;

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

//*****************************************************************************
//*                                                                            
//* 1- using arg_check we check if the number of arguments is correct
//* 2- using extentions_check we check if the map file has the correct
//*    extension
//* 3- using get_string we read the map file and we save it as a string and
//*    save it in tmp variable.
//* 4- We check if there is anything in tmp variable.
//* 5- We check if there are newlines between map lines of the map file.
//* 6- we split the map file by newlines and save it in raw_file variable 
//*    in the map structure.
//* 7- using trim_empty_lines we trim the empty lines from the end of raw_file
//*    variable.
//* 8- using parse_map we parse the textures and colors and the map part.
//* 9- since we saved everything in the map structure we can free tmp variable.
//* 
//*****************************************************************************
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
		return (free(tmp), ft_perror("wrong format", EINVAL), 1);
	(*map)->raw_file = ft_split(tmp, '\n');
	if (!(*map)->raw_file)
		return (free(tmp), ft_perror("malloc", errno), 1);
	trim_empty_lines(&((*map)->raw_file));
	if (parse_map(map))
		return (free(tmp), 1);
	free(tmp);
	return (0);
}
