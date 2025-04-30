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

//*****************************************************************************
//*                                                                           
//* 1- we check if the number of arguments is correct and if we recieve       
//*    --test-mlx we call the test_mlx function                           
//* 2- using init_map we allocate memory for the map structure and initialize
//*    the structures with the correct starting values
//* 3- using init_map_mlx we initialize the mlx and the window related
//*    variables.
//* 4- if we fail in step 2 or 3 we return 1
//* 5- using init_player we initialize the player related variables
//* 6- using parse_args we parse map file and check if it is valid and create
//*    the map structure with required values.
//* 7- using start_game we start the game, we load the textures and we render
//*    the game.
//* 8- using cleanup we free the memory and close the window
//* 
//*****************************************************************************

int	main(int ac, char **av)
{
	t_file	*map;

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
		cleanup(&map);
		return (1);
	}
	cleanup(&map);
	return (0);
}
