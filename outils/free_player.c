/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:40:45 by edouard           #+#    #+#             */
/*   Updated: 2024/02/19 21:16:59 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void free_sprites(void *mlx_ptr, void **sprites, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		if (sprites[i])
		{
			mlx_destroy_image(mlx_ptr, sprites[i]);
			sprites[i] = NULL;
		}
		i++;
	}
}

void free_player(t_resources *res)
{
	if (res->player)
	{

		free_sprites(res->data.mlx_ptr, (void **)res->player->sprites_up, 5);
		free_sprites(res->data.mlx_ptr, (void **)res->player->sprites_down, 5);
		free_sprites(res->data.mlx_ptr, (void **)res->player->sprites_left, 5);
		free_sprites(res->data.mlx_ptr, (void **)res->player->sprites_right, 5);
		free(res->player);
		res->player = NULL;
	}
}

void display_steps(t_resources *resources)
{
	char *steps_str = ft_itoa(resources->player->steps);
	if (!steps_str)
		return;

	char *prefix = "Steps: ";
	char *final = ft_strjoin(prefix, steps_str);
	free(steps_str);

	if (!final)
		return;

	int text_x = 40;
	int text_y = 40;
	int color = 0xFF0000;

	mlx_string_put(resources->data.mlx_ptr, resources->data.win_ptr, text_x, text_y, color, final);
	free(final);
}
