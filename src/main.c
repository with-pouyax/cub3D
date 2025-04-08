/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:27:25 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/14 09:25:57 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//first we put pixel in to the buffer and next we gonna display it
void	put_pixel(int x, int y, int color, t_mlx *game)
{
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	int i = y * game->img_ptr.line_length + x * game->img_ptr.bits_per_pixel / 8;
	game->img_ptr.addr[i] = color &  0xFF;
	game->img_ptr.addr[i + 1] = (color >> 8) &  0xFF;
	game->img_ptr.addr[i + 2] = (color >> 16) &  0xFF;
	
}
void	draw_square(int x, int y, int size, int color, t_mlx *game)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			put_pixel(x + j, y + i, color, game);
	}
}

int	main(int ac, char **av)
{
	t_file	*map;

	// Test MLX if requested
	if (ac == 2 && !ft_strncmp(av[1], "--test-mlx", 10))
		return (test_mlx());

	if (init_map(&map) || init_map_mlx(&map))
		return (1);
	init_player(map);
	if (parse_args(ac, av, &map))
	{
		cleanup(&map);
		return (1);
	}
	if (start_game(&map))
	{
		cleanup(&map); // Now cleanup handles MLX resources too
		return (1);
	}
	printf("\nwe are good to go\n");
	
	cleanup(&map);
	return (0);
}
