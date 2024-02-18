/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_outils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 22:12:00 by edouard           #+#    #+#             */
/*   Updated: 2024/02/16 16:10:45 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void update_map_for_player(t_game_map *map, t_player *player)
{
	if (map->map_data[player->prev_y][player->prev_x] == 'P')
		map->map_data[player->prev_y][player->prev_x] = '0';

	map->map_data[player->y][player->x] = 'P';

	player->prev_x = player->x;
	player->prev_y = player->y;
}

void handle_player_movement(int keysym, t_resources *res)
{
	int newX = res->player->x;
	int newY = res->player->y;

	switch (keysym)
	{
	case 6: // W
		newY -= 1;
		res->player->direction = 'W';
		break;
	case 12: // A
		newX -= 1;
		res->player->direction = 'A';
		break;
	case 1: // S
		newY += 1;
		res->player->direction = 'S';
		break;
	case 2: // D
		newX += 1;
		res->player->direction = 'D';
		break;
	default:
		res->player->is_moving = false;
		return;
	}

	if (newX >= 0 && newX < res->game_map->map_length && newY >= 0 && newY < res->game_map->map_height)
	{
		if (res->game_map->map_data[newY][newX] == 'C')
		{
			res->sheep_count--;
			printf("Sheep count: %d\n", res->sheep_count);
			// Можете добавить здесь дополнительную логику, например, проверку на завершение уровня
		}
		if (res->game_map->map_data[newY][newX] == 'E' && res->sheep_count == 0)
		{
			end_game(res, 1);
		}
		if (res->game_map->map_data[newY][newX] != '1')
		{
			res->player->x = newX;
			res->player->y = newY;
			res->player->is_moving = true;
			res->player->steps++;
			update_map_for_player(res->game_map, res->player);
		}
		else
		{
			res->player->is_moving = false;
		}
	}
}
