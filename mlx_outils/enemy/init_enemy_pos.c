/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemy_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:36:39 by edouard           #+#    #+#             */
/*   Updated: 2024/02/13 22:26:00 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_pos *get_available_positions_for_enemies(t_resources *resources, int *available_positions_count)
{
	int y;
	int x;
	int max_possible_positions = resources->game_map->map_length * resources->game_map->map_height;
	t_pos *available_positions = (t_pos *)malloc(sizeof(t_pos) * max_possible_positions);
	if (!available_positions)
		return NULL;
	y = 0;
	int count = 0;
	while (y < resources->game_map->map_height)
	{
		x = 0;
		while (x < resources->game_map->map_length)
		{
			if (resources->game_map->map_data[y][x] == '0')
			{
				available_positions[count].x = x;
				available_positions[count].y = y;
				count++;
			}
			x++;
		}
		y++;
	}
	*available_positions_count = count;
	return available_positions;
}
