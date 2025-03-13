/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:29:46 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/13 15:29:47 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void print_whole_structure_in_order(t_file *map)
{
	int	r, g, b;

	printf("\n========================================\n");
	printf("            CUB3D MAP STRUCTURE         \n");
	printf("========================================\n\n");

	// Texture paths
	printf(">>> TEXTURE PATHS <<<\n");
	printf("  ▸ North : %s\n", map->textures.north);
	printf("  ▸ South : %s\n", map->textures.south);
	printf("  ▸ West  : %s\n", map->textures.west);
	printf("  ▸ East  : %s\n\n", map->textures.east);

	// Colors
	printf(">>> COLORS <<<\n");

	r = (map->colors.floor >> 16) & 0xFF;
	g = (map->colors.floor >> 8) & 0xFF;
	b = map->colors.floor & 0xFF;
	printf("  ▸ Floor  : RGB(%3d, %3d, %3d) | Hex: 0x%06X\n", r, g, b, map->colors.floor);

	r = (map->colors.ceiling >> 16) & 0xFF;
	g = (map->colors.ceiling >> 8) & 0xFF;
	b = map->colors.ceiling & 0xFF;
	printf("  ▸ Ceiling: RGB(%3d, %3d, %3d) | Hex: 0x%06X\n\n", r, g, b, map->colors.ceiling);

	// Map dimensions
	printf(">>> MAP DIMENSIONS <<<\n");
	printf("  ▸ Width : %d\n", map->map_width);
	printf("  ▸ Height: %d\n\n", map->map_height);

	// Player info
	printf(">>> PLAYER INFORMATION <<<\n");
	printf("  ▸ Direction: %c\n", map->player_dir);
	printf("  ▸ Position : (%d, %d)\n\n", map->player_x, map->player_y);

	// Game map
	printf(">>> GAME MAP <<<\n");
	for (int i = 0; map->game_map[i]; i++)
		printf("  %s\n", map->game_map[i]);

	printf("\n========================================\n");
} 