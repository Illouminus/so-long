/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_route.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 20:51:00 by edouard           #+#    #+#             */
/*   Updated: 2024/02/13 22:14:18 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

#include <stdbool.h>

// Функция для проверки существования пути
bool check_path_exists(char **map, int width, int height, int startX, int startY, int itemsCount)
{
	bool exitFound = false;
	int itemsLeft = itemsCount;
	bool **visited = malloc(height * sizeof(bool *));

	for (int i = 0; i < height; i++)
	{
		visited[i] = ft_calloc(width, sizeof(bool));
	}

	flood_fill(startX, startY, map, visited, width, height, &exitFound, &itemsLeft);

	// Освобождаем память
	for (int i = 0; i < height; i++)
	{
		free(visited[i]);
	}
	free(visited);

	return exitFound && itemsLeft == 0;
}

// Реализация flood fill
void flood_fill(int x, int y, char **map, bool **visited, int width, int height, bool *exitFound, int *itemsLeft)
{
	if (x < 0 || x >= width || y < 0 || y >= height || visited[y][x] || map[y][x] == '1')
		return;

	visited[y][x] = true; // Отмечаем клетку как посещённую

	if (map[y][x] == 'E' && *itemsLeft == 0)
	{
		*exitFound = true;
		return;
	}

	if (map[y][x] == 'C')
	{
		(*itemsLeft)--;
	}

	// Рекурсивно исследуем соседние клетки
	flood_fill(x + 1, y, map, visited, width, height, exitFound, itemsLeft);
	flood_fill(x - 1, y, map, visited, width, height, exitFound, itemsLeft);
	flood_fill(x, y + 1, map, visited, width, height, exitFound, itemsLeft);
	flood_fill(x, y - 1, map, visited, width, height, exitFound, itemsLeft);
}
