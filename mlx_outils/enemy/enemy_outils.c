/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:46:07 by edouard           #+#    #+#             */
/*   Updated: 2024/02/16 15:34:15 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void upload_enemy_sprite(t_resources *resources, t_enemy *enemy, int index)
{

	char *index_str = ft_itoa(index + 1);
	char *path = ft_strjoin("./textures/enemy/enemy_", index_str);
	char *full_path = ft_strjoin(path, ".xpm");
	free(path);
	free(index_str);
	enemy->sprites[index] = mlx_xpm_file_to_image(resources->data.mlx_ptr, full_path,
																 &resources->game_map->usual_texture_width,
																 &resources->game_map->usual_texture_height);
	free(full_path);

	if (!(enemy->sprites[index]))
	{
		free_resources(resources);
		print_errors("Error: Failed to load enemy sprite\n");
	}
}

static void upload_enemy_sprites(t_resources *resources, int enemy_index)
{

	t_enemy *current_enemy;
	int i;
	current_enemy = &resources->enemy[enemy_index];
	i = 0;
	while (i < current_enemy->frame_count)
	{
		upload_enemy_sprite(resources, current_enemy, i);
		i++;
	}
}

void init_one_enemy(t_enemy *enemy, t_resources *resources)
{

	enemy->current_sprite = 0;
	enemy->last_update = clock();
	enemy->frame_count = 8;
	enemy->is_moving = false;
	enemy->sprites = malloc(sizeof(void *) * enemy->frame_count);
	if (!enemy->sprites)
	{
		free_resources(resources);
		print_errors("Malloc error in enemy sprites allocation\n");
		return;
	}
}

void init_enemy(t_resources *resources)
{
	int i = 0;
	int available_positions_count = 0;
	resources->enemy_count = 4;
	t_pos *available_positions = get_available_positions_for_enemies(resources, &available_positions_count);

	if (!available_positions || available_positions_count < resources->enemy_count)
	{
		printf("Not enough space for enemies\n");
		free(available_positions);
		return;
	}

	resources->enemy = malloc(sizeof(t_enemy) * resources->enemy_count);
	if (!resources->enemy)
	{
		free(available_positions); // Освобождаем память для массива доступных позиций
		free_resources(resources);
		print_errors("Malloc error in init enemy function\n");
	}

	init_enemy_positions(resources, available_positions, available_positions_count); // Используем изменённый вызов

	for (i = 0; i < resources->enemy_count; i++)
	{
		init_one_enemy(&(resources->enemy[i]), resources);
		upload_enemy_sprites(resources, i);
	}

	free(available_positions); // Освобождаем память для массива доступных позиций после его использования
}

void drawEnemy(t_resources *resources, t_enemy *enemy)
{

	if (enemy->sprites)
	{
		void *sprite_to_draw = enemy->sprites[enemy->current_sprite];
		if (sprite_to_draw)
		{
			mlx_put_image_to_window(resources->data.mlx_ptr, resources->data.win_ptr, sprite_to_draw, enemy->x * 64, enemy->y * 64);
		}
	}
}
