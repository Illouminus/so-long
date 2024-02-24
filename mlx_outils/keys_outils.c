/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_outils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 22:12:00 by edouard           #+#    #+#             */
/*   Updated: 2024/02/24 17:38:12 by ebaillot         ###   ########.fr       */
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
	if (keysym == 119)
	{
		(*newY)--;
		res->player->direction = 'W';
	}
	else if (keysym == 97)
	{
		(*newX)--;
		res->player->direction = 'A';
	}
	else if (keysym == 115)
	{
		(*newY)++;
		res->player->direction = 'S';
	}
	else if (keysym == 100)
	{
		(*newX)++;
		res->player->direction = 'D';
	}
	else
		res->player->is_moving = false;
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
	int	new_x;
	int	new_y;

	new_x = res->player->x;
	new_y = res->player->y;
	update_player_position(keysym, res, &new_x, &new_y);
	if (!res->player->is_moving)
		return ;
	if (check_collision(res, new_x, new_y))
	{
		res->player->x = new_x;
		res->player->y = new_y;
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
