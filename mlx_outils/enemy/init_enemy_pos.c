/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemy_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:36:39 by edouard           #+#    #+#             */
/*   Updated: 2024/03/08 15:33:06 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	add_available_position(t_pos *available_positions, int *count, int x,
		int y)
{
	available_positions[*count].x = x;
	available_positions[*count].y = y;
	(*count)++;
}

t_pos	*get_available_positions_for_enemies(t_resources *resources,
		int *available_positions_count)
{
	int		y;
	int		x;
	t_pos	*available_positions;
	int		count;

	available_positions = (t_pos *)malloc(sizeof(t_pos)
			* (resources->game_map->map_length
				* resources->game_map->map_height));
	if (!available_positions)
		return (NULL);
	y = 0;
	count = 0;
	while (y < resources->game_map->map_height)
	{
		x = 0;
		while (x < resources->game_map->map_length)
		{
			if (resources->game_map->map_data[y][x] == '0')
				add_available_position(available_positions, &count, x, y);
			x++;
		}
		y++;
	}
	*available_positions_count = count;
	return (available_positions);
}

void	draw_enemy(t_resources *resources, t_enemy *enemy)
{
	void	*sprite_to_draw;

	if (enemy->sprites)
	{
		sprite_to_draw = enemy->sprites[enemy->current_sprite];
		if (sprite_to_draw)
		{
			mlx_put_image_to_window(resources->data.mlx_ptr,
				resources->data.win_ptr, sprite_to_draw, enemy->x * 64, enemy->y
				* 64);
		}
	}
}

void	upload_enemy_sprite(t_resources *resources, t_enemy *enemy, int index)
{
	char	*index_str;
	char	*path;
	char	*full_path;

	index_str = ft_itoa(index + 1);
	path = ft_strjoin("./textures/enemy/enemy_", index_str);
	full_path = ft_strjoin(path, ".xpm");
	free(path);
	free(index_str);
	enemy->sprites[index] = mlx_xpm_file_to_image(resources->data.mlx_ptr,
			full_path, &resources->game_map->usual_texture_width,
			&resources->game_map->usual_texture_height);
	free(full_path);
	if (!(enemy->sprites[index]))
	{
		free_resources(resources);
		print_errors("Error: Failed to load enemy sprite\n");
	}
}

void	fill_directions(int directions[4][2])
{
	directions[0][0] = 0;
	directions[0][1] = -1;
	directions[1][0] = 0;
	directions[1][1] = 1;
	directions[2][0] = -1;
	directions[2][1] = 0;
	directions[3][0] = 1;
	directions[3][1] = 0;
}
