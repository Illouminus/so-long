/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_outils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 20:58:13 by edouard           #+#    #+#             */
/*   Updated: 2024/02/11 21:25:43 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void init_additional_options(t_resources *resources)
{
	resources->player->x = 0;
	resources->player->y = 0;
	resources->player->current_sprite = 0;
	resources->player->last_update = clock();
	resources->player->direction = 'D';
	resources->player->is_moving = false;
	resources->player->frame_count = 5;
	resources->player->sprites_up = NULL;
	resources->player->sprites_down = NULL;
	resources->player->sprites_left = NULL;
	resources->player->sprites_right = NULL;
}

void init_player(t_resources *resources)
{
	resources->player = malloc(sizeof(t_player));
	if (!resources->player)
	{
		free_resources(resources);
		print_errors("Malloc error in init player function\n");
	}
	init_additional_options(resources);
	resources->player->sprites_up = malloc(sizeof(void *) * 5);
	if (!resources->player->sprites_up)
		free_resources(resources);
	resources->player->sprites_down = malloc(sizeof(void *) * 5);
	if (!resources->player->sprites_down)
		free_resources(resources);
	resources->player->sprites_left = malloc(sizeof(void *) * 5);
	if (!resources->player->sprites_left)
		free_resources(resources);
	resources->player->sprites_right = malloc(sizeof(void *) * 5);
	if (!resources->player->sprites_right)
		free_resources(resources);

	upload_player_sprites(resources);
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
