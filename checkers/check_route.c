/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_route.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 20:51:00 by edouard           #+#    #+#             */
/*   Updated: 2024/02/24 17:51:12 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	flood_fill_util(t_flood_fill_data *data, int x, int y)
{
	if (x < 0 || x >= data->map->map_length || y < 0
		|| y >= data->map->map_height || data->visited[y][x]
		|| data->map->map_data[y][x] == '1')
		return ;
	data->visited[y][x] = true;
	if (data->map->map_data[y][x] == 'C')
		data->items_left--;
	if (data->map->map_data[y][x] == 'E' && data->items_left == 0)
		data->exit_found = true;
	flood_fill_util(data, x + 1, y);
	flood_fill_util(data, x - 1, y);
	flood_fill_util(data, x, y + 1);
	flood_fill_util(data, x, y - 1);
}

bool	check_path_exists(t_game_map *map, int itemsCount)
{
	t_flood_fill_data	data;
	int					i;

	i = 0;
	data.map = map;
	data.exit_found = false;
	data.items_left = itemsCount;
	data.visited = malloc(map->map_height * sizeof(bool *));
	while (i < map->map_height)
	{
		data.visited[i] = ft_calloc(map->map_length, sizeof(bool));
		i++;
	}
	flood_fill_util(&data, map->player_position_x, map->player_position_y);
	i = 0;
	while (i < map->map_height)
	{
		free(data.visited[i]);
		i++;
	}
	free(data.visited);
	return (data.exit_found && data.items_left == 0);
}
