/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:51:12 by edouard           #+#    #+#             */
/*   Updated: 2024/02/11 20:02:44 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void ft_load_first_layer(t_resources *res)
{
	int y;
	int x;

	y = 0;
	while (y < res->game_map->map_height)
	{
		x = 0;
		while (x < res->game_map->map_length)
		{
			mlx_put_image_to_window(res->data.mlx_ptr, res->data.win_ptr, res->game_map->floor, x * 32, y * 32);
			x++;
		}
		y++;
	}
}

void ft_load_second_layer(t_resources *res)
{
	int y;
	int x;

	y = 0;
	while (y < res->game_map->map_height)
	{
		x = 0;
		while (x < res->game_map->map_length)
		{
			if (res->game_map->map_data[y][x] == '1')
			{
				if (y == 0 || y == res->game_map->map_height - 1 || x == 0 || x == res->game_map->map_length - 2)
					mlx_put_image_to_window(res->data.mlx_ptr, res->data.win_ptr, res->game_map->wall, x * 32, y * 32);
				else
					mlx_put_image_to_window(res->data.mlx_ptr, res->data.win_ptr, res->game_map->wall_map, x * 32, y * 32);
			}
			x++;
		}
		y++;
	}
}

void ft_load_three_layer(t_resources *res)
{
	int y;
	int x;

	y = 0;
	while (y < res->game_map->map_height)
	{
		x = 0;
		while (x < res->game_map->map_length)
		{
			if (res->game_map->map_data[y][x] == 'P')
			{
				res->player->y = y;
				res->player->x = x;
				drawPlayer(&res->data, res->player);
			}
			if (res->game_map->map_data[y][x] == 'C')
			{
				res->sheep->y = y;
				res->sheep->x = x;
				drawSheep(&res->data, res->sheep);
			}
			x++;
		}
		y++;
	}
}
