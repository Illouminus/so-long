/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_outils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 22:12:00 by edouard           #+#    #+#             */
/*   Updated: 2024/01/28 22:19:35 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void handle_player_movement(int keysym, t_player *player)
{
	player->is_moving = true; // Устанавливаем флаг движения

	switch (keysym)
	{
	case KEY_W: // Перемещение вверх
		player->y -= 1;
		player->direction = 'W';
		break;
	case KEY_A: // Перемещение влево
		player->x -= 1;
		player->direction = 'A';
		break;
	case KEY_S: // Перемещение вниз
		player->y += 1;
		player->direction = 'S';
		break;
	case KEY_D: // Перемещение вправо
		player->x += 1;
		player->direction = 'D';
		break;
	default:
		player->is_moving = false; // Если нажатая клавиша не WASD, не двигаемся
		break;
	}
}
