/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:16:52 by edouard           #+#    #+#             */
/*   Updated: 2024/02/24 15:45:03 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	*load_texture(void *mlx_ptr, char *path, int *width, int *height)
{
	void	*img;

	img = mlx_xpm_file_to_image(mlx_ptr, path, width, height);
	if (!img)
	{
		return (NULL);
	}
	return (img);
}

void	ft_load_textures(t_resources *res)
{
	res->game_map->floor = load_texture(res->data.mlx_ptr,
			"./textures/floor.xpm", &res->game_map->usual_texture_width,
			&res->game_map->usual_texture_height);
	res->game_map->wall = load_texture(res->data.mlx_ptr, "./textures/wall.xpm",
			&res->game_map->usual_texture_width,
			&res->game_map->usual_texture_height);
	res->game_map->wall_map = load_texture(res->data.mlx_ptr,
			"./textures/wall_map.xpm", &res->game_map->usual_texture_width,
			&res->game_map->usual_texture_height);
	res->game_map->exit = load_texture(res->data.mlx_ptr, "./textures/exit.xpm",
			&res->game_map->usual_texture_width,
			&res->game_map->usual_texture_height);
	if (!res->game_map->floor || !res->game_map->wall
		|| !res->game_map->wall_map || !res->game_map->exit)
	{
		ft_free_textures(res);
		print_errors("Error\nFailed to load one or more textures");
	}
}

void	ft_put_textures(t_resources *res)
{
	ft_load_first_layer(res);
	ft_load_second_layer(res);
	ft_load_three_layer(res);
}

void	ft_free_textures(t_resources *res)
{
	if (res->game_map->wall)
		mlx_destroy_image(res->data.mlx_ptr, res->game_map->wall);
	if (res->game_map->floor)
		mlx_destroy_image(res->data.mlx_ptr, res->game_map->floor);
	if (res->game_map->wall_map)
		mlx_destroy_image(res->data.mlx_ptr, res->game_map->wall_map);
	if (res->game_map->exit)
		mlx_destroy_image(res->data.mlx_ptr, res->game_map->exit);
}
