/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:58:00 by edouard           #+#    #+#             */
/*   Updated: 2024/02/20 14:50:58 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void update_map_for_enemy(t_game_map *map, t_enemy *enemy, t_resources *res)
{
	char currentPosition;
	if (map->map_data[enemy->prev_y][enemy->prev_x] == 'N')
		map->map_data[enemy->prev_y][enemy->prev_x] = '0';

	currentPosition = map->map_data[enemy->y][enemy->x];
	if (currentPosition == 'P')
		end_game(res, 0);
	if (currentPosition != 'C' && currentPosition != 'N')
		map->map_data[enemy->y][enemy->x] = 'N';

	enemy->prev_x = enemy->x;
	enemy->prev_y = enemy->y;
}

static bool canMoveTo(t_game_map *map, int x, int y)
{
	char cell;

	if (x < 1 || x >= map->map_length || y < 1 || y >= map->map_height)
		return false;

	cell = map->map_data[y][x];

	if (cell == '1' || cell == 'C' || cell == 'N')
		return false;

	return true;
}

void updateEnemyPatrol(t_resources *resources)
{
	int directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
	int i = 0;
	int attempt;
	int dirIndex;
	int dx, dy;
	bool moved;

	while (i < resources->enemy_count)
	{
		moved = false;
		attempt = 0;

		while (attempt < 4 && !moved)
		{
			dirIndex = rand() % 4;
			dx = directions[dirIndex][0];
			dy = directions[dirIndex][1];

			if (canMoveTo(resources->game_map, resources->enemy[i].x + dx, resources->enemy[i].y + dy))
			{
				resources->enemy[i].x += dx;
				resources->enemy[i].y += dy;
				moved = true;
			}
			attempt++;
		}
		update_map_for_enemy(resources->game_map, &resources->enemy[i], resources);
		i++;
	}
}

void updateEnemyAnimation(t_enemy *enemy, int interval)
{
	clock_t current_time = clock();
	if ((current_time - enemy->last_update) > (clock_t)interval)
	{
		enemy->current_sprite = (enemy->current_sprite + 1) % enemy->frame_count;
		enemy->last_update = current_time;
	}
}