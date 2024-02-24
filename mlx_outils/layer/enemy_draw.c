/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:07:11 by edouard           #+#    #+#             */
/*   Updated: 2024/02/24 17:31:22 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	init_enemy_positions(t_resources *resources, t_pos *available_positions,
		int available_positions_count)
{
	int	random_index;
	int	i;

	i = 0;
	srand(time(NULL));
	while (i < resources->enemy_count)
	{
		random_index = rand() % available_positions_count;
		resources->enemy[i].x = available_positions[random_index].x;
		resources->enemy[i].y = available_positions[random_index].y;
		resources->enemy[i].prev_x = available_positions[random_index].x;
		resources->enemy[i].prev_y = available_positions[random_index].y;
		resources->game_map->map_data[
			resources->enemy[i].y][resources->enemy[i].x] = 'N';
		available_positions[
			random_index] = available_positions[available_positions_count
			- 1];
		available_positions_count--;
		i++;
	}
}

void	free_enemys_sprites(t_resources *res)
{
	int	i;
	int	j;

	i = 0;
	while (i < res->enemy_count)
	{
		j = 0;
		while (j < res->enemy[i].frame_count)
		{
			if (res->enemy[i].sprites[j])
				mlx_destroy_image(res->data.mlx_ptr, res->enemy[i].sprites[j]);
			j++;
		}
		free(res->enemy[i].sprites);
		i++;
	}
}
