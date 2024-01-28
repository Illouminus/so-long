/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sheep_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:34:48 by edouard           #+#    #+#             */
/*   Updated: 2024/01/28 18:43:46 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void init_sheep(t_sheep **sheep)
{
	(*sheep)->sprites = malloc(sizeof(void *) * 4);
	(*sheep)->current_sprite = 0;
	(*sheep)->last_update = clock();
	(*sheep)->is_collected = false;
	(*sheep)->x = 0;
	(*sheep)->y = 0;
}

void init_and_load_sheep(t_data *data, t_sheep **sheep, t_game_map **map)
{
	int i;
	char *str;
	i = 0;
	init_sheep(sheep);
	while (i < 4)
	{
		str = ft_strjoin("./textures/sheep/sheep_", ft_itoa(i + 1));
		str = ft_strjoin(str, ".xpm");
		(*sheep)->sprites[i] = mlx_xpm_file_to_image(data->mlx_ptr, str, &(*map)->usual_texture_width, &(*map)->usual_texture_height);

		if (!(*sheep)->sprites[i])
		{
			printf("Failed to load sprite %d\n", i);
			return;
		}
		i++;
	}
}

void updateSheepAnimation(t_sheep *sheep, int interval, int sprite_count)
{

	if (sheep->is_collected)
		return;
	clock_t current_time = clock();

	// Проверяем, пора ли обновить анимацию
	if ((current_time - sheep->last_update) > (unsigned long)interval)
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
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, sheep->sprites[sheep->current_sprite], sheep->x * 32, sheep->y * 32);
		}
	}
}
