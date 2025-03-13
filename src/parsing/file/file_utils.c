/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:28:59 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/13 15:29:00 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int file_length(char *file_name)
{
    int fd;
    char c;
    int ret;
    int length;

    length = 0;
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        return (ft_perror("", errno), -1);
    ret = read(fd, &c, 1);
    while (ret > 0)
    {
        length++;
        ret = read(fd, &c, 1);
    }
    if (ret < 0)
    {
        safe_close(fd);
        return (ft_perror("", errno), -1);
    }
    return (length);
}
    
int copy_file(char *file_name, char **file, int file_len)
{
    int fd;
    int ret;

    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        return (1);
    ret = read(fd, *file, file_len);
    if (ret < 0)
        return (1);
    (*file)[file_len] = '\0';
    safe_close(fd);
    return (0);
}
    
char *get_string(int *file_len, char **av)
{
    char *tmp;

    tmp = NULL;
    *file_len = file_length(av[1]);
    if (*file_len < 0)
        return (NULL);
    tmp = malloc(*file_len + 1);
    if (!tmp)
        return (ft_perror("malloc", errno), NULL);
    if (copy_file(av[1], &tmp, *file_len))
    {
        free(tmp);
        tmp = NULL;
    }
    return (tmp);
}

int is_empty_line(char *line)
{
	int j;

	j = 0;
	if (!line)
		return (1);
	while (line[j]) // we iterate through the line
	{
		if (line[j] != ' ' && line[j] != '\t')
			return (1);
		j++;
	}
	return (0);
}

void trim_empty_lines(char ***map)
{
	int i;
	int last_non_empty;

	i = 0;
	last_non_empty = -1;
	while ((*map)[i])
	{
		if (is_empty_line((*map)[i]))
			last_non_empty = i; // we store the index of the last non empty line
		i++;
	}
	if (last_non_empty < i - 1) // if the last non empty line is less than the last line means there are empty lines at the end
	{
		i = last_non_empty + 1;
		while ((*map)[i]) // we iterate from the last non empty line to the last line
		{
			free((*map)[i]); 
			(*map)[i] = NULL;
			i++;
		}
	}
} 