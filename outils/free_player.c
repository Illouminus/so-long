/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:40:45 by edouard           #+#    #+#             */
/*   Updated: 2024/02/11 17:23:36 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void free_sprites(void **sprites, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		if (sprites[i])
			free(sprites[i]);
		i++;
	}
}

void free_player(t_player *player)
{
	if (player)
	{
		free_sprites((void **)player->sprites_up, 5);
		free_sprites((void **)player->sprites_down, 5);
		free_sprites((void **)player->sprites_left, 5);
		free_sprites((void **)player->sprites_right, 5);

		free(player->sprites_up);
		free(player->sprites_down);
		free(player->sprites_left);
		free(player->sprites_right);

		free(player);
	}

	exit(1);
}