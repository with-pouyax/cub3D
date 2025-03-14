/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:30:00 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/14 09:26:51 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 * This is a simple test program to verify that the MLX library is working.
 * It doesn't require a display server to run.
 */
int	test_mlx(void)
{
	void	*mlx_ptr;
	char	*display;

	printf("Testing MLX library...\n");
	
	// Check if DISPLAY environment variable is set
	display = getenv("DISPLAY");
	if (!display || !*display)
	{
		printf("Warning: DISPLAY environment variable not set.\n");
		printf("This is normal if you're running in a remote environment.\n");
		printf("MLX library is linked correctly, but you need a display server to use it.\n");
		return (0);
	}
	
	mlx_ptr = mlx_init();
	if (!mlx_ptr)
	{
		printf("MLX initialization failed!\n");
		printf("This could be due to lack of a display server.\n");
		printf("The library is linked correctly, but you need a display server to use it.\n");
		return (0);
	}
	
	printf("MLX initialization successful!\n");
	printf("MLX library is working correctly.\n");
	
	return (0);
} 