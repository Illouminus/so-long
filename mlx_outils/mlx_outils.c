/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_outils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:57:41 by ebaillot          #+#    #+#             */
/*   Updated: 2024/01/29 10:11:01 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void load_map(t_data *data, t_game_map **map, t_sheep *sheep, t_player *player)
{
	ft_load_textures(data, map);
	init_and_load_sheep(data, &sheep, map);
	init_player(&player, data, map);
	ft_put_textures(data, map, sheep, player);
}
