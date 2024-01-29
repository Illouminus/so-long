/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_outils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 22:12:00 by edouard           #+#    #+#             */
/*   Updated: 2024/01/29 22:31:42 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void update_map_for_player(t_game_map *map, t_player *player)
{
	int y = 0;
	int x;

	// Ищем старое положение игрока и заменяем его на '0'
	while (y < map->map_height)
	{
		x = 0;
		while (x < map->map_length)
		{
			if (map->map_data[y][x] == 'P')
			{
				map->map_data[y][x] = '0'; // предполагаем, что '0' - это пустое пространство
			}
			x++;
		}
		y++;
	}

	// Устанавливаем новое положение игрока
	map->map_data[player->y][player->x] = 'P';
}

void handle_player_movement(int keysym, t_player *player, t_game_map *map)
{
	int newX = player->x;
	int newY = player->y;

	switch (keysym)
	{
	case 6: // W
		newY -= 1;
		player->direction = 'W';
		break;
	case 12: // A
		newX -= 1;
		player->direction = 'A';
		break;
	case 1: // S
		newY += 1;
		player->direction = 'S';
		break;
	case 2: // D
		newX += 1;
		player->direction = 'D';
		break;
	default:
		printf("Invalid Key: %d\n", keysym);
		player->is_moving = false;
		return;
	}

	if (newX >= 0 && newX < map->map_length && newY >= 0 && newY < map->map_height && map->map_data[newY][newX] != '1')
	{
		player->x = newX;
		player->y = newY;
		player->is_moving = true;
		update_map_for_player(map, player);
	}
	else
	{
		printf("Blocked or Invalid Move\n");
		player->is_moving = false;
	}
}
