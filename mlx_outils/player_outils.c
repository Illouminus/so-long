/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_outils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 20:58:13 by edouard           #+#    #+#             */
/*   Updated: 2024/02/11 13:04:18 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void init_additional_options(t_player **player)
{
	(*player)->x = 0;
	(*player)->y = 0;
	(*player)->current_sprite = 0;
	(*player)->last_update = clock();
	(*player)->direction = 'D';
	(*player)->is_moving = false;
	(*player)->frame_count = 5;
	(*player)->sprites_up = NULL;
	(*player)->sprites_down = NULL;
	(*player)->sprites_left = NULL;
	(*player)->sprites_right = NULL;
}

void init_player(t_player **player, t_data *data, t_game_map **map)
{
	*player = malloc(sizeof(t_player));
	if (!(*player))
	{
		free_game_map(map);
		exit(1);
	}
	init_additional_options(player);
	(*player)->sprites_up = malloc(sizeof(void *) * 5);
	if (!(*player)->sprites_up)
		free_error_malloc_player(*player, map);
	(*player)->sprites_down = malloc(sizeof(void *) * 5);
	if (!(*player)->sprites_down)
		free_error_malloc_player(*player, map);
	(*player)->sprites_left = malloc(sizeof(void *) * 5);
	if (!(*player)->sprites_left)
		free_error_malloc_player(*player, map);
	(*player)->sprites_right = malloc(sizeof(void *) * 5);
	if (!(*player)->sprites_right)
		free_error_malloc_player(*player, map);

	upload_player_sprites(player, data, map);
}

void updatePlayerAnimation(t_player *player, int interval)
{
	clock_t current_time = clock();

	if (player->is_moving)
	{
		if ((current_time - player->last_update) > (unsigned long)interval)
		{
			player->current_sprite = (player->current_sprite + 1) % player->frame_count;
			player->last_update = current_time;
		}
	}
	else
		player->current_sprite = 0;
}

void drawPlayer(t_data *data, t_player *player)
{

	void *sprite_to_draw = NULL;

	switch (player->direction)
	{
	case 'W':
		sprite_to_draw = player->sprites_up[player->current_sprite];
		break;
	case 'S':
		sprite_to_draw = player->sprites_down[player->current_sprite];
		break;
	case 'A':
		sprite_to_draw = player->sprites_left[player->current_sprite];
		break;
	case 'D':
		sprite_to_draw = player->sprites_right[player->current_sprite];
		break;
	}

	if (sprite_to_draw)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, sprite_to_draw, player->x * 32, player->y * 32);
	}
}
