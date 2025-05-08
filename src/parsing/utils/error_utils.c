/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoushma <mhoushma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:29:51 by pghajard          #+#    #+#             */
/*   Updated: 2025/05/08 13:39:10 by mhoushma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//*****************************************************************************
//*                                                                            
//* 1- we check if the error is not 0
//* 2- if the error is not 0 we set the errno to the error, it is a macro that
//*    sets the errno to the error number that we get from the perror function
//* 3- else we print the message we get from the perror function using perror
//*    ft_putstr_fd.
//*****************************************************************************

void	ft_perror(char *msg, int err)
{
	ft_putstr_fd("Error\n", 2);
	if (err)
	{
		errno = err;
		perror(msg);
	}
	else
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
}

void	pexit(char *msg, int err, int exit_code)
{
	ft_perror(msg, err);
	exit(exit_code);
}

//*****************************************************************************
//*                                                                            
//* 1- we check if the file is valid
//* 2- we save the length of the file name in len variable
//* 3- we loop through the file name from the end to the start as long as the
//*    character is a space or a tab.
//* 4- if the length is less than 5 means the file name is not valid because
//*    it need to have at least 4 characters and a dot (.cub)
//* 5- if the last 4 characters are not .cub we return an error
//* 6- if the length is greater than 4 and the 5th character is a / means 
//*    the file name is not valid because it is .cub and it has no extension.
//* 7- if the file name is valid we return 0
//* 
//*****************************************************************************
int	extentions_check(char *file)
{
	int	len;

	if (!file)
		return (ft_perror("extension", EINVAL), 1);
	len = ft_strlen(file);
	while (len > 0 && (file[len - 1] == ' ' || file[len - 1] == '\t'))
		len--;
	if (len < 5)
		return (ft_perror("extension", EINVAL), 1);
	if (ft_strncmp(file + len - 4, ".cub", 4))
		return (ft_perror("extension", EINVAL), 1);
	if (len > 4 && file[len - 5] == '/')
		return (ft_perror("extension", EINVAL), 1);
	return (0);
}

int	arg_check(int ac)
{
	if (ac != 2)
	{
		ft_perror("honey", EINVAL);
		return (1);
	}
	return (0);
}

//*****************************************************************************
//*                                                                            
//* 1- we check if the file descriptor is not -1
//* 2- if the file descriptor is not -1 we close the file
//* 3- if the file descriptor is -1 means the file is not open and we don't
//*    need to close it
//* 
//*****************************************************************************
int	safe_close(int fd)
{
	if (fd != -1)
	{
		if (close(fd) < 0)
			return (-1);			
	}
	return (0);
}
