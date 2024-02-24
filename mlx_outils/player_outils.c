/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_outils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 20:58:13 by edouard           #+#    #+#             */
/*   Updated: 2024/02/24 17:40:47 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	init_additional_options(t_resources *resources)
{
	resources->player->x = 0;
	resources->player->y = 0;
	resources->player->prev_x = 0;
	resources->player->prev_y = 0;
	resources->player->current_sprite = 0;
	resources->player->steps = 0;
	resources->player->last_update = clock();
	resources->player->direction = 'D';
	resources->player->is_moving = false;
	resources->player->frame_count = 5;
	resources->player->sprites_up = NULL;
	resources->player->sprites_down = NULL;
	resources->player->sprites_left = NULL;
	resources->player->sprites_right = NULL;
}

void	init_player(t_resources *resources)
{
	resources->player = malloc(sizeof(t_player));
	if (!resources->player)
		free_resources(resources);
	init_additional_options(resources);
	resources->player->sprites_up = malloc(sizeof(void *) * 5);
	resources->player->sprites_down = malloc(sizeof(void *) * 5);
	resources->player->sprites_left = malloc(sizeof(void *) * 5);
	resources->player->sprites_right = malloc(sizeof(void *) * 5);
	if (!resources->player->sprites_up || !resources->player->sprites_down
		|| !resources->player->sprites_left
		|| !resources->player->sprites_right)
	{
		free(resources->player->sprites_up);
		free(resources->player->sprites_down);
		free(resources->player->sprites_left);
		free(resources->player->sprites_right);
		free(resources->player);
		free_resources(resources);
		return ;
	}
	upload_player_sprites(resources);
}

void	update_player_animation(t_player *player, int interval)
{
	clock_t	current_time;

	current_time = clock();
	if (player->is_moving)
	{
		if ((current_time - player->last_update) > (clock_t)interval)
		{
			player->current_sprite = (player->current_sprite + 1)
				% player->frame_count;
			player->last_update = current_time;
		}
	}
	else
		player->current_sprite = 0;
}

void	draw_player(t_resources *resources)
{
	t_player	*player;
	void		*sprite_to_draw;

	player = resources->player;
	sprite_to_draw = NULL;
	if (player->direction == 'W')
		sprite_to_draw = player->sprites_up[player->current_sprite];
	else if (player->direction == 'S')
		sprite_to_draw = player->sprites_down[player->current_sprite];
	else if (player->direction == 'A')
		sprite_to_draw = player->sprites_left[player->current_sprite];
	else if (player->direction == 'D')
		sprite_to_draw = player->sprites_right[player->current_sprite];
	if (sprite_to_draw)
	{
		mlx_put_image_to_window(resources->data.mlx_ptr,
			resources->data.win_ptr, sprite_to_draw, player->x * 64, player->y
			* 64);
	}
}
