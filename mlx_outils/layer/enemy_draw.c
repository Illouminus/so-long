/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:07:11 by edouard           #+#    #+#             */
/*   Updated: 2024/02/13 19:28:18 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void enemy_count(t_resources *res)
{
	int y;
	int x;

	res->enemy_count = 0;
	y = 0;
	while (y < res->game_map->map_height)
	{
		x = 0;
		while (x < res->game_map->map_length)
		{
			if (res->game_map->map_data[y][x] == 'N')
				res->enemy_count++;
			x++;
		}
		y++;
	}
}

void init_enemy_positions(t_resources *resources, t_pos *available_positions, int available_positions_count)
{
	srand(time(NULL)); // Инициализация генератора случайных чисел

	for (int i = 0; i < resources->enemy_count; i++)
	{
		if (available_positions_count == 0)
		{
			printf("Error: No available positions for enemies\n");
			return;
		}

		int random_index = rand() % available_positions_count;
		int enemy_x = available_positions[random_index].x;
		int enemy_y = available_positions[random_index].y;

		resources->enemy[i].x = enemy_x;
		resources->enemy[i].y = enemy_y;
		resources->enemy[i].prev_x = enemy_x;
		resources->enemy[i].prev_y = enemy_y;

		resources->game_map->map_data[enemy_y][enemy_x] = 'N'; // Обновление карты с позицией врага

		available_positions[random_index] = available_positions[available_positions_count - 1];
		available_positions_count--;
	}
}

void free_enemys_sprites(t_resources *res)
{
	int i;
	int j;

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