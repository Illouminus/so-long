/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_outils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 20:58:13 by edouard           #+#    #+#             */
/*   Updated: 2024/01/29 10:38:33 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void init_player(t_player **player, t_data *data, t_game_map **map)
{
	printf("Initializing player...\n");
	*player = malloc(sizeof(t_player));
	if (!(*player))
		return; // Обработка ошибки выделения памяти

	(*player)->sprites_up = malloc(sizeof(void *) * 5);
	(*player)->sprites_down = malloc(sizeof(void *) * 5);
	(*player)->sprites_left = malloc(sizeof(void *) * 5);
	(*player)->sprites_right = malloc(sizeof(void *) * 5);

	upload_player_sprites(player, data, map);

	(*player)->x = 0; // Начальная позиция X
	printf("player->x = %d\n", (*player)->x);
	(*player)->y = 0; // Начальная позиция Y
	(*player)->current_sprite = 0;
	(*player)->last_update = clock();
	(*player)->direction = 'R'; // Направление по умолчанию
	(*player)->is_moving = false;
	(*player)->frame_count = 5; // Количество спрайтов для каждого направления
}

void updatePlayerAnimation(t_player *player, int interval)
{
	clock_t current_time = clock();

	if (!player->is_moving)
		return;

	if ((current_time - player->last_update) > (unsigned long)interval)
	{
		player->current_sprite = (player->current_sprite + 1) % player->frame_count;
		player->last_update = current_time;
	}
}

void drawPlayer(t_data *data, t_player *player)
{
	if (player->is_moving)
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
}
