/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:29:51 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/13 16:34:32 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_perror(char *msg, int err)
{
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

int	extentions_check(char *file)
{
	int	len;

	if (!file)
		return (ft_perror("Error", EINVAL), 1);
	len = ft_strlen(file);
	while (len > 0 && (file[len - 1] == ' ' || file[len - 1] == '\t'))
		len--;
	if (len < 5)
		return (ft_perror("Error", EINVAL), 1);
	if (ft_strncmp(file + len - 4, ".cub", 4))
		return (ft_perror("Error", EINVAL), 1);
	if (len > 4 && file[len - 5] == '/')
		return (ft_perror("Error", EINVAL), 1);
	return (0);
}

int	arg_check(int ac)
{
	if (ac != 2)
	{
		ft_perror("Error", EINVAL);
		return (1);
	}
	return (0);
}

void safe_close(int fd)
{
    if (fd != -1)
    {
        if (close(fd) < 0)
            ft_perror("close", errno); // Report error but don't exit
    }
}
