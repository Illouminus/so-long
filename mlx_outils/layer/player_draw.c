/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:01:48 by edouard           #+#    #+#             */
/*   Updated: 2024/02/24 17:43:03 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	player_draw_layer(t_resources *res, int y, int x)
{
	res->player->y = y;
	res->player->x = x;
	res->player->prev_y = y;
	res->player->prev_x = x;
	draw_player(res);
}
