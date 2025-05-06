/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_rgb_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoushma <mhoushma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:29:26 by pghajard          #+#    #+#             */
/*   Updated: 2025/05/06 14:23:35 by mhoushma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//*****************************************************************************
//*                                                                            
//* 1- we skip the white spaces after the identifier
//* 2- using no_xpm_extension we check texture file extension
//* 3- we copy the texture path to the dest variable
//*****************************************************************************
int	extract_and_assign_path(char *line, char **dest)
{
	char	*path;

	path = line + 3;
	while (*path && (*path == ' ' || *path == '\t'))
		path++;
	if (no_xpm_extension(line))
		return (1);
	*dest = ft_strdup(path);
	if (!*dest)
		return (ft_perror("malloc failed", ENOMEM), 1);
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

//*****************************************************************************
//*                                                                            
//* 1- we skip the white spaces
//* 2- we check if if the current character is a digit
//* 3- if it is a digit we convert it to an integer
//* 4- we return the integer
//*****************************************************************************
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
		if (value > INT_MAX / 10 || (value == INT_MAX / 10 \
		&& (str[*i] - '0') > INT_MAX % 10))
			return (-1);
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
