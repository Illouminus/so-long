/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:45:20 by edouard           #+#    #+#             */
/*   Updated: 2024/01/28 22:05:18 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void upload_player_sprites_right(t_player **player, t_data *data, t_game_map **map)
{
	int i;
	char *str;
	i = 0;

	while (i < 5)
	{
		str = ft_strjoin("./textures/player/right_side/player_right_", ft_itoa(i + 1));
		str = ft_strjoin(str, ".xpm");
		(*player)->sprites_right[i] = mlx_xpm_file_to_image(data->mlx_ptr, str, &(*map)->usual_texture_width, &(*map)->usual_texture_height);

		if (!(*player)->sprites_right[i])
		{
			printf("Failed to load sprite %d\n", i);
			return;
		}
		i++;
	}
}

static void upload_player_sprites_left(t_player **player, t_data *data, t_game_map **map)
{
	int i;
	char *str;
	i = 0;

	while (i < 5)
	{
		str = ft_strjoin("./textures/player/left_side/player_left_", ft_itoa(i + 1));
		str = ft_strjoin(str, ".xpm");
		(*player)->sprites_left[i] = mlx_xpm_file_to_image(data->mlx_ptr, str, &(*map)->usual_texture_width, &(*map)->usual_texture_height);

		if (!(*player)->sprites_left[i])
		{
			printf("Failed to load sprite %d\n", i);
			return;
		}
		i++;
	}
}

static void upload_player_sprites_up(t_player **player, t_data *data, t_game_map **map)
{
	int i;
	char *str;
	i = 0;

	while (i < 5)
	{
		str = ft_strjoin("./textures/player/up/player_up_", ft_itoa(i + 1));
		str = ft_strjoin(str, ".xpm");
		(*player)->sprites_up[i] = mlx_xpm_file_to_image(data->mlx_ptr, str, &(*map)->usual_texture_width, &(*map)->usual_texture_height);

		if (!(*player)->sprites_up[i])
		{
			printf("Failed to load sprite %d\n", i);
			return;
		}
		i++;
	}
}

static void upload_player_sprites_down(t_player **player, t_data *data, t_game_map **map)
{
	int i;
	char *str;
	i = 0;

	while (i < 5)
	{
		str = ft_strjoin("./textures/player/down/player_down_", ft_itoa(i + 1));
		str = ft_strjoin(str, ".xpm");
		(*player)->sprites_down[i] = mlx_xpm_file_to_image(data->mlx_ptr, str, &(*map)->usual_texture_width, &(*map)->usual_texture_height);

		if (!(*player)->sprites_down[i])
		{
			printf("Failed to load sprite %d\n", i);
			return;
		}
		i++;
	}
}

void upload_player_sprites(t_player **player, t_data *data, t_game_map **map)
{
	upload_player_sprites_right(player, data, map);
	upload_player_sprites_left(player, data, map);
	upload_player_sprites_up(player, data, map);
	upload_player_sprites_down(player, data, map);
}