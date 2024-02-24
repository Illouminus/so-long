/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:40:45 by edouard           #+#    #+#             */
/*   Updated: 2024/02/24 17:48:23 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	free_sprites(void *mlx_ptr, void **sprites, int count)
{
	int	i;

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

void	free_player(t_resources *res)
{
	if (res->player)
	{
		free_sprites(res->data.mlx_ptr, (void **)res->player->sprites_up, 5);
		free_sprites(res->data.mlx_ptr, (void **)res->player->sprites_down, 5);
		free_sprites(res->data.mlx_ptr, (void **)res->player->sprites_left, 5);
		free_sprites(res->data.mlx_ptr, (void **)res->player->sprites_right, 5);
		free(res->player->sprites_up);
		free(res->player->sprites_down);
		free(res->player->sprites_left);
		free(res->player->sprites_right);
		free(res->player);
		res->player = NULL;
	}
}

void	display_steps(t_resources *resources)
{
	char	*steps_str;
	char	*prefix;
	char	*final;
	int		color;

	steps_str = ft_itoa(resources->player->steps);
	if (!steps_str)
		return ;
	prefix = "Steps: ";
	final = ft_strjoin(prefix, steps_str);
	free(steps_str);
	if (!final)
		return ;
	color = 0xFF0000;
	mlx_string_put(resources->data.mlx_ptr, resources->data.win_ptr, 100, 100,
		color, final);
	free(final);
}

void	upload_player_sprite(t_resources *resources, void **sprite,
		const char *path_prefix, int index)
{
	char	*index_str;
	char	*path;
	char	*full_path;

	index_str = ft_itoa(index + 1);
	path = ft_strjoin(path_prefix, index_str);
	full_path = ft_strjoin(path, ".xpm");
	free(index_str);
	free(path);
	*sprite = mlx_xpm_file_to_image(resources->data.mlx_ptr, full_path,
			&resources->game_map->usual_texture_width,
			&resources->game_map->usual_texture_height);
	free(full_path);
	if (!(*sprite))
	{
		free_resources(resources);
	}
}
