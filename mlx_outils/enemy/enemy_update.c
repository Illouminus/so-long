/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:58:00 by edouard           #+#    #+#             */
/*   Updated: 2024/02/24 17:27:00 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	update_map_for_enemy(t_game_map *map, t_enemy *enemy,
		t_resources *res)
{
	char	current_position;

	if (map->map_data[enemy->prev_y][enemy->prev_x] == 'N')
		map->map_data[enemy->prev_y][enemy->prev_x] = '0';
	current_position = map->map_data[enemy->y][enemy->x];
	if (current_position == 'P')
		end_game(res, 0);
	if (current_position != 'C' && current_position != 'N')
		map->map_data[enemy->y][enemy->x] = 'N';
	enemy->prev_x = enemy->x;
	enemy->prev_y = enemy->y;
}

static bool	can_move_to(t_game_map *map, int x, int y)
{
	char	cell;

	if (x < 1 || x >= map->map_length || y < 1 || y >= map->map_height)
		return (false);
	cell = map->map_data[y][x];
	if (cell == '1' || cell == 'C' || cell == 'N')
		return (false);
	return (true);
}

bool	choose_enemy_direction(t_resources *resources, int i,
		int (*directions)[2])
{
	int		attempt;
	bool	moved;
	int		dir_index;
	int		dx;
	int		dy;

	attempt = 0;
	moved = false;
	while (attempt < 4 && !moved)
	{
		dir_index = rand() % 4;
		dx = directions[dir_index][0];
		dy = directions[dir_index][1];
		if (can_move_to(resources->game_map, resources->enemy[i].x + dx,
				resources->enemy[i].y + dy))
		{
			resources->enemy[i].x += dx;
			resources->enemy[i].y += dy;
			moved = true;
		}
		attempt++;
	}
	return (moved);
}

void	update_enemy_patrol(t_resources *resources)
{
	int	directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
	int	i;

	i = 0;
	while (i < resources->enemy_count)
	{
		if (choose_enemy_direction(resources, i, directions))
		{
			update_map_for_enemy(resources->game_map, &resources->enemy[i],
				resources);
		}
		i++;
	}
}

void	update_enemy_animation(t_enemy *enemy, int interval)
{
	clock_t	current_time;

	current_time = clock();
	if ((current_time - enemy->last_update) > (clock_t)interval)
	{
		enemy->current_sprite = (enemy->current_sprite + 1)
			% enemy->frame_count;
		enemy->last_update = current_time;
	}
}
