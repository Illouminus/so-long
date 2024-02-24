/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_outils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 22:12:00 by edouard           #+#    #+#             */
/*   Updated: 2024/02/24 15:42:08 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	update_map_for_player(t_game_map *map, t_player *player)
{
	if (map->map_data[player->prev_y][player->prev_x] == 'P')
		map->map_data[player->prev_y][player->prev_x] = '0';
	map->map_data[player->y][player->x] = 'P';
	player->prev_x = player->x;
	player->prev_y = player->y;
}

void	update_player_position(int keysym, t_resources *res, int *newX,
		int *newY)
{
	switch (keysym)
	{
	case 119: // W
		(*newY)--;
		res->player->direction = 'W';
		break ;
	case 97: // A
		(*newX)--;
		res->player->direction = 'A';
		break ;
	case 115: // S
		(*newY)++;
		res->player->direction = 'S';
		break ;
	case 100: // D
		(*newX)++;
		res->player->direction = 'D';
		break ;
	default:
		res->player->is_moving = false;
		return ;
	}
	res->player->is_moving = true;
}

bool	check_collision(t_resources *res, int newX, int newY)
{
	int	i;

	if (newX < 0 || newX >= res->game_map->map_length || newY < 0
		|| newY >= res->game_map->map_height
		|| res->game_map->map_data[newY][newX] == '1')
	{
		return (false);
	}
	i = 0;
	while (i < res->enemy_count)
	{
		if (newX == res->enemy[i].x && newY == res->enemy[i].y)
			end_game(res, 0);
		i++;
	}
	if (res->game_map->map_data[newY][newX] == 'C')
		res->sheep_count--;
	if (res->game_map->map_data[newY][newX] == 'E' && res->sheep_count == 0)
		end_game(res, 1);
	return (true);
}

void	move_player(int keysym, t_resources *res)
{
	int	newX;
	int	newY;

	newX = res->player->x;
	newY = res->player->y;
	update_player_position(keysym, res, &newX, &newY);
	if (!res->player->is_moving)
		return ;
	if (check_collision(res, newX, newY))
	{
		res->player->x = newX;
		res->player->y = newY;
		res->player->steps++;
		update_map_for_player(res->game_map, res->player);
	}
	else
	{
		res->player->is_moving = false;
	}
}

void	handle_player_movement(int keysym, t_resources *res)
{
	move_player(keysym, res);
}
