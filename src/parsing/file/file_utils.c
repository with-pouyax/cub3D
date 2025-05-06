/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:28:59 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/13 17:01:07 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	file_length(char *file_name)
{
	int		fd;
	char	c;
	int		ret;
	int		length;

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
		if(safe_close(fd))
			return (-1);
	}
	return (length);
}

//*****************************************************************************
//*                                                                            
//* 1- we open the file
//* 2- we read the file and we save it in the file variable
//* 3- we set the last character of the file to the null character
//* because it is a string and we need to end it with a null character
//* 4- we close the file safely
//* 5- we return 0
//*****************************************************************************

int	copy_file(char *file_name, char **file, int file_len)
{
	int	fd;
	int	ret;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (1);
	ret = read(fd, *file, file_len);
	if (ret < 0)
		return (1);
	(*file)[file_len] = '\0';
	if (safe_close(fd))
		return (1);
	return (0);
}

//*****************************************************************************
//*                                                                            
//* 1- we get the length of the file
//* 2- we allocate memory for the file
//* 3- we copy the file to the allocated memory
//* 4- we return the file
//* 
//*****************************************************************************

char	*get_string(int *file_len, char **av)
{
	char	*tmp;

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

int	is_empty_line(char *line)
{
	int	j;

	j = 0;
	if (!line)
		return (1);
	while (line[j])
	{
		if (line[j] != ' ' && line[j] != '\t')
			return (1);
		j++;
	}
	return (0);
}

//*****************************************************************************
//*                                                                            
//* 1- ***map is the array of strings that contains the map in our case it is
//*    the raw_file variable in the map structure.
//* 2- we loop through each member (line) of the array.
//* 3- by calling is_empty_line we check if the line is empty.
//* 4- if the line is empty we save the index of the last non-empty line 
//*    (member) in last_non_empty variable.
//* 5- we continue this process until the end of the array.
//* 6- so after the loop i will have the index of the last + 1 member of the
//*    array.
//* 7- is last_non_empty < i - 1 means we have empty lines at the end of the
//*    array.
//* 8- so in this case we set i to last_non_empty + 1 means we start from the
//*    last non-empty line.
//* 9- we loop until the end of the array and we free the empty lines and set
//*    them to NULL.
//* 10- like this we trim the empty lines from the end of the array.
//*
//*****************************************************************************
void	trim_empty_lines(char ***map)
{
	int	i;
	int	last_non_empty;

	i = 0;
	last_non_empty = -1;
	while ((*map)[i])
	{
		if (is_empty_line((*map)[i]))
			last_non_empty = i;
		i++;
	}
	if (last_non_empty < i - 1)
	{
		i = last_non_empty + 1;
		while ((*map)[i])
		{
			free((*map)[i]);
			(*map)[i] = NULL;
			i++;
		}
	}
}
