/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:45:20 by edouard           #+#    #+#             */
/*   Updated: 2024/02/24 17:42:41 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	upload_player_sprites_right(t_resources *resources)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		upload_player_sprite(resources, &resources->player->sprites_right[i],
			"./textures/player/right_side/player_right_", i);
		i++;
	}
}

static void	upload_player_sprites_left(t_resources *resources)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		upload_player_sprite(resources, &resources->player->sprites_left[i],
			"./textures/player/left_side/player_left_", i);
		i++;
	}
}

static void	upload_player_sprites_up(t_resources *resources)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		upload_player_sprite(resources, &resources->player->sprites_up[i],
			"./textures/player/up/player_up_", i);
		i++;
	}
}

static void	upload_player_sprites_down(t_resources *resources)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		upload_player_sprite(resources, &resources->player->sprites_down[i],
			"./textures/player/down/player_down_", i);
		i++;
	}
}

void	upload_player_sprites(t_resources *resources)
{
	upload_player_sprites_right(resources);
	upload_player_sprites_left(resources);
	upload_player_sprites_up(resources);
	upload_player_sprites_down(resources);
}
