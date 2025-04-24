/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pghajard <pghajard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:27:25 by pghajard          #+#    #+#             */
/*   Updated: 2025/03/15 15:27:25 by pghajard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

void	move_forward(t_file *map)
{
	move_up_down(map, FORWARD);
}

void	move_backward(t_file *map)
{
	move_up_down(map, BACKWARD);
}

void	move_leftward(t_file *map)
{
	move_right_left(map, LEFTWARD);
}

void	move_rightward(t_file *map)
{
	move_right_left(map, RIGHTWARD);
}
