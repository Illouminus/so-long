/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:13:23 by edouard           #+#    #+#             */
/*   Updated: 2024/02/13 16:36:10 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void free_resources(t_resources *res)
{
	if (!res)
		return;

	if (res->game_map)
	{
		free_game_map(&res->game_map);
		res->game_map = NULL;
	}

	if (res->player)
	{
		free_player(res->player);
		res->player = NULL;
	}

	if (res->sheep)
	{
		free(res->sheep);
		res->sheep = NULL;
	}
	if (res->enemy)
	{
		free_enemys_sprites(res);
		free(res->enemy);
		res->enemy = NULL;
	}

	if (res->data.win_ptr)
	{
		mlx_destroy_window(res->data.mlx_ptr, res->data.win_ptr);
		res->data.win_ptr = NULL;
	}
}

void end_game(t_resources *res, int win)
{

	if (win)
	{
		printf("You Win!\n");
		mlx_string_put(res->data.mlx_ptr, res->data.win_ptr, 100, 100, 0xFF0000, "You Win!");
		// mlx_clear_window(res->data.mlx_ptr, res->data.win_ptr);
	}
	else
	{
		// Вывод сообщения о проигрыше
		mlx_string_put(res->data.mlx_ptr, res->data.win_ptr, 100, 100, 0xFF0000, "Game Over!");
	}

	// Дать время на прочтение сообщения перед закрытием
	sleep(2); // Используйте usleep() в микросекундах для более точного контроля

	free_resources(res); // Освобождение ресурсов
	exit(0);					// Завершение программы
}
