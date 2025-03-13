/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color_utils1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:29:31 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/13 16:29:09 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_texture_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return ((line[i] == 'N' && line[i + 1] == 'O' && \
	(line[i + 2] == ' ' || line[i + 2] == '\t')) || \
	(line[i] == 'S' && line[i + 1] == 'O' && \
	(line[i + 2] == ' ' || line[i + 2] == '\t')) || \
	(line[i] == 'W' && line[i + 1] == 'E' && \
	(line[i + 2] == ' ' || line[i + 2] == '\t')) || \
	(line[i] == 'E' && line[i + 1] == 'A' && \
	(line[i + 2] == ' ' || line[i + 2] == '\t')));
}

int	is_color_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return ((line[i] == 'F' && (line[i + 1] == ' ' || \
	line[i + 1] == '\t')) || \
	(line[i] == 'C' && (line[i + 1] == ' ' || line[i + 1] == '\t')));
}

int	get_identifier_position(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

int	process_no_texture(t_file *map, char *line, t_dir_flags *dir_flags)
{
	dir_flags->no++;
	if (dir_flags->no > 1)
		return (ft_perror("duplicate NO texture", EINVAL), 1);
	if (extract_and_assign_path(line, &map->textures.north))
		return (1);
	return (0);
}

int	process_so_texture(t_file *map, char *line, t_dir_flags *dir_flags)
{
	dir_flags->so++;
	if (dir_flags->so > 1)
		return (ft_perror("duplicate SO texture", EINVAL), 1);
	if (extract_and_assign_path(line, &map->textures.south))
		return (1);
	return (0);
}
