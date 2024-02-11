/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:13:23 by edouard           #+#    #+#             */
/*   Updated: 2024/02/11 19:46:19 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void free_resources(t_resources *res)
{
	if (!res)
		return;

	if (res->game_map)
	{
		free_game_map(&res->game_map);
		res->game_map = NULL;
	}

	if (res->player)
	{
		free_player(res->player);
		res->player = NULL;
	}

	if (res->sheep)
	{
		free(res->sheep);
		res->sheep = NULL;
	}

	if (res->data.win_ptr)
	{
		mlx_destroy_window(res->data.mlx_ptr, res->data.win_ptr);
		res->data.win_ptr = NULL;
	}
}
