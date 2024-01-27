/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:16:52 by edouard           #+#    #+#             */
/*   Updated: 2024/01/27 21:23:08 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void ft_load_textures(t_data *data, t_game_map **map)
{
	(*map)->floor = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/floor.xpm", &(*map)->usual_texture_width, &(*map)->usual_texture_height);
	if (!(*map)->floor)
	{
		ft_free_textures(data, map);
		exit(0);
	}
	(*map)->wall = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/wall.xpm", &(*map)->usual_texture_width, &(*map)->usual_texture_height);
	if (!(*map)->wall)
	{
		ft_free_textures(data, map);
		exit(0);
	}
	(*map)->wall_map = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/wall_map.xpm", &(*map)->usual_texture_width, &(*map)->usual_texture_height);
	if (!(*map)->wall_map)
	{
		ft_free_textures(data, map);
		exit(0);
	}
}

void ft_put_textures(t_data *data, t_game_map **map)
{
	ft_load_first_layer(data, map);
	ft_load_second_layer(data, map);
}

void ft_free_textures(t_data *data, t_game_map **map)
{
	if ((*map)->wall)
		mlx_destroy_image(data->mlx_ptr, (*map)->wall);
	if ((*map)->floor)
		mlx_destroy_image(data->mlx_ptr, (*map)->floor);
	if ((*map)->player)
		mlx_destroy_image(data->mlx_ptr, (*map)->player);
	if ((*map)->exit)
		mlx_destroy_image(data->mlx_ptr, (*map)->exit);
	if ((*map)->items)
		mlx_destroy_image(data->mlx_ptr, (*map)->items);
	if ((*map)->enemy)
		mlx_destroy_image(data->mlx_ptr, (*map)->enemy);
	if ((*map)->end_img)
		mlx_destroy_image(data->mlx_ptr, (*map)->end_img);
}