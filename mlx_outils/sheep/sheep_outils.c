/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sheep_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:34:48 by edouard           #+#    #+#             */
/*   Updated: 2024/02/24 14:25:41 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void free_sheep_sprites(t_sheep *sheep, void *mlx_ptr)
{
	if (sheep && sheep->sprites)
	{
		int i = 0;
		while (i < 4)
		{
			if (sheep->sprites[i])
			{
				mlx_destroy_image(mlx_ptr, sheep->sprites[i]);
			}
			i++;
		}
		free(sheep->sprites);
	}
}

static void init_sheep(t_resources *res)
{
	int i;

	res->sheep->sprites = malloc(sizeof(void *) * 4);
	if (!res->sheep->sprites)
	{
		free_resources(res);
		print_errors("Failed to allocate memory for sheep sprites\n");
	}
	i = 0;
	while (i < 4)
	{
		res->sheep->sprites[i] = NULL;
		i++;
	}
	res->sheep->current_sprite = 0;
	res->sheep->last_update = clock();
	res->sheep->is_collected = false;
	res->sheep->x = 0;
	res->sheep->y = 0;
}

void init_and_load_sheep(t_resources *res)
{
	int i;
	char *str;
	char *temp;
	char *number_sheep;

	i = 0;
	init_sheep(res);
	sheep_count(res);

	while (i < 4)
	{
		number_sheep = ft_itoa(i + 1);
		temp = ft_strjoin("./textures/sheep/sheep_", number_sheep);
		str = ft_strjoin(temp, ".xpm");
		free(temp);
		free(number_sheep);
		res->sheep->sprites[i] = mlx_xpm_file_to_image(res->data.mlx_ptr, str, &res->game_map->usual_texture_width, &res->game_map->usual_texture_height);
		free(str);
		if (!res->sheep->sprites[i])
			free_resources(res);
		i++;
	}
}

void updateSheepAnimation(t_sheep *sheep, int interval, int sprite_count)
{

	if (sheep->is_collected)
		return;
	clock_t current_time = clock();

	// Проверяем, пора ли обновить анимацию
	if ((current_time - sheep->last_update) > (clock_t)interval)
	{
		sheep->current_sprite = (sheep->current_sprite + 1) % sprite_count;
		sheep->last_update = current_time;
	}
}

// Функция для отрисовки овцы
void drawSheep(t_data *data, t_sheep *sheep)
{

	if (sheep->sprites)
	{
		if (!sheep->is_collected)
		{
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, sheep->sprites[sheep->current_sprite], sheep->x * 64, sheep->y * 64);
		}
	}
}
