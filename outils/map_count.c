/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:40:40 by edouard           #+#    #+#             */
/*   Updated: 2024/02/19 20:51:32 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void set_player_position(t_resources *res)
{
	int y;
	int x;

	y = 0;
	while (y < res->game_map->map_height)
	{
		x = 0;
		while (x < res->game_map->map_length)
		{
			if (res->game_map->map_data[y][x] == 'P')
			{
				res->game_map->player_position_y = y;
				res->game_map->player_position_x = x;
			}
			x++;
		}
		y++;
	}
}

void init_array_null(void **array, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		array[i] = NULL;
		i++;
	}
}