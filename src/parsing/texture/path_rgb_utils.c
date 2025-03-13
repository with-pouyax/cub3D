/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_rgb_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:29:26 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/13 16:25:53 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	extract_and_assign_path(char *line, char **dest)
{
	char	*path;

	path = line + 3;
	while (*path && (*path == ' ' || *path == '\t'))
		path++;
	if (no_xpm_extension(line))
		return (ft_perror("Texture file must have .xpm extension", EINVAL), 1);
	*dest = ft_strdup(path);
	if (!*dest)
		return (ft_perror("malloc", errno), 1);
	return (0);
}

int	wrong_rgb(char *line)
{
	int	i;
	int	len;
	int	comma_count;

	i = 1;
	len = ft_strlen(line);
	comma_count = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\t'))
		len--;
	while (i < len)
	{
		if (line[i] == ',')
			comma_count++;
		else if (!ft_isdigit(line[i]) && line[i] != ' ' && line[i] != '\t')
			return (1);
		i++;
	}
	if (comma_count != 2)
		return (1);
	return (0);
}

int	parse_rgb_value(char *str, int *i)
{
	int	value;

	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	if (!str[*i] || !ft_isdigit(str[*i]))
		return (-1);
	value = 0;
	while (str[*i] && ft_isdigit(str[*i]))
	{
		value = value * 10 + (str[*i] - '0');
		if (value > 255)
			return (-1);
		(*i)++;
	}
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	return (value);
}

int	extract_rgb(char *line, int *rgb_value)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 1;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	r = parse_rgb_value(line, &i);
	if (r < 0 || r > 255 || line[i++] != ',')
		return (1);
	g = parse_rgb_value(line, &i);
	if (g < 0 || g > 255 || line[i++] != ',')
		return (1);
	b = parse_rgb_value(line, &i);
	if (b < 0 || b > 255)
		return (1);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i])
		return (1);
	*rgb_value = (r << 16) | (g << 8) | b;
	return (0);
}
