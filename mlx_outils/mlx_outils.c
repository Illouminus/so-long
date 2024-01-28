/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_outils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:57:41 by ebaillot          #+#    #+#             */
/*   Updated: 2024/01/28 15:54:40 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void load_map(t_data *data, t_game_map **map, t_sheep *sheep)
{
	ft_load_textures(data, map);
	init_and_load_sheep(data, &sheep, map);
	ft_put_textures(data, map, sheep);
}
