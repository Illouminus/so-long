/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:16:52 by edouard           #+#    #+#             */
/*   Updated: 2024/02/11 20:03:24 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void ft_load_textures(t_resources *res)
{
	res->game_map->floor = mlx_xpm_file_to_image(res->data.mlx_ptr, "./textures/floor.xpm", &res->game_map->usual_texture_width, &res->game_map->usual_texture_height);
	if (!res->game_map->floor)
	{
		ft_free_textures(res);
		print_errors("Error\nFailed to load floor texture");
	}
	res->game_map->wall = mlx_xpm_file_to_image(res->data.mlx_ptr, "./textures/wall.xpm", &res->game_map->usual_texture_width, &res->game_map->usual_texture_height);
	if (!res->game_map->wall)
	{
		ft_free_textures(res);
		print_errors("Error\nFailed to load wall texture");
	}
	res->game_map->wall_map = mlx_xpm_file_to_image(res->data.mlx_ptr, "./textures/wall_map.xpm", &res->game_map->usual_texture_width, &res->game_map->usual_texture_height);
	if (!res->game_map->wall_map)
	{
		ft_free_textures(res);
		print_errors("Error\nFailed to load wall_map texture");
	}
	// Добавьте здесь загрузку других текстур по аналогии
}

void ft_put_textures(t_resources *res)
{
	ft_load_first_layer(res);
	ft_load_second_layer(res);
	ft_load_three_layer(res);
}

void ft_free_textures(t_resources *res)
{
	if (res->game_map->wall)
		mlx_destroy_image(res->data.mlx_ptr, res->game_map->wall);
	if (res->game_map->floor)
		mlx_destroy_image(res->data.mlx_ptr, res->game_map->floor);
	if (res->game_map->exit)
		mlx_destroy_image(res->data.mlx_ptr, res->game_map->exit);
	if (res->game_map->sheep && res->game_map->sheep->sprites[0])
		mlx_destroy_image(res->data.mlx_ptr, res->game_map->sheep->sprites[0]);
	if (res->game_map->enemy)
		mlx_destroy_image(res->data.mlx_ptr, res->game_map->enemy);
	if (res->game_map->end_img)
		mlx_destroy_image(res->data.mlx_ptr, res->game_map->end_img);
	free_resources(res);
}
