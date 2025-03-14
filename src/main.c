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

// Function declaration from test_mlx.c
int	test_mlx(void);

// we NULL and 0 all the fields of the mlx part of the map



int	init_map_mlx(t_file **map)
{
	// Initialize MLX members
	(*map)->mlx.mlx = NULL;
	(*map)->mlx.win = NULL;
	// Initialize IMG members
	(*map)->img.img = NULL;
	(*map)->img.addr = NULL;
	(*map)->img.bits_per_pixel = 0;
	(*map)->img.line_length = 0;
	(*map)->img.endian = 0;
	return (0);
}

int	init_mlx(t_file **map)
{
	(*map)->mlx.mlx = mlx_init(); // in failure, mlx_init returns NULL
	if (!(*map)->mlx.mlx)
		return (1);
	return (0);
}

int	create_window(t_file **map)
{
	(*map)->mlx.win = mlx_new_window((*map)->mlx.mlx, 1000, 1000, "Cub3D");
	if (!(*map)->mlx.win)
		return (1);
	return (0);
}

int	start_game(t_file *map)
{
	if (init_mlx(&map))
		return (1);
	if (create_window(&map))
		return (1);
	
	return (0);
}


void cleanup_mlx(t_file *map)
{
	if (map->mlx.mlx)
		mlx_destroy_display(map->mlx.mlx);
	if (map->mlx.win)
		mlx_destroy_window(map->mlx.mlx, map->mlx.win);
	if (map->img.img)
		mlx_destroy_image(map->mlx.mlx, map->img.img);
}

int	main(int ac, char **av)
{
	t_file	*map;

	// Test MLX if requested
	if (ac == 2 && !ft_strncmp(av[1], "--test-mlx", 10))
		return (test_mlx());

	if (init_map(&map) || init_map_mlx(&map))
		return (1);

	if (parse_args(ac, av, &map))
	{
		cleanup(&map);
		return (1);
	}

	if (start_game(map))
	{
		cleanup_mlx(map);
		cleanup(&map);
		return (1);
	}
	printf("\nwe are good to go\n");
	
	cleanup(&map);
	return (0);
}
