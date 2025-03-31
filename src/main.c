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
