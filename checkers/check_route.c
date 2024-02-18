/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_route.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 20:51:00 by edouard           #+#    #+#             */
/*   Updated: 2024/02/16 17:55:58 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void flood_fill(int x, int y, char **map, bool **visited, int width, int height, bool *exitFound, int *itemsLeft)
{
	// Проверка границ карты, уже посещенных клеток и стен
	if (x < 0 || x >= width || y < 0 || y >= height || visited[y][x] || map[y][x] == '1')
		return;

	visited[y][x] = true; // Отметить клетку как посещенную

	// Обработка клетки с предметом
	if (map[y][x] == 'C')
		(*itemsLeft)--;

	// Проверка на выход
	if (map[y][x] == 'E' && *itemsLeft == 0)
	{
		*exitFound = true;
		// Не возвращаемся, чтобы продолжить исследование карты
	}

	// Рекурсивный обход во все стороны
	flood_fill(x + 1, y, map, visited, width, height, exitFound, itemsLeft);
	flood_fill(x - 1, y, map, visited, width, height, exitFound, itemsLeft);
	flood_fill(x, y + 1, map, visited, width, height, exitFound, itemsLeft);
	flood_fill(x, y - 1, map, visited, width, height, exitFound, itemsLeft);
}

bool check_path_exists(char **map, int width, int height, int startX, int startY, int itemsCount)
{
	printf("width %d, height %d, startX %d, startY %d, itemsCount %d\n", width, height, startX, startY, itemsCount);
	bool exitFound = false;
	int itemsLeft = itemsCount;
	bool **visited = malloc(height * sizeof(bool *));

	for (int i = 0; i < height; i++)
	{
		visited[i] = ft_calloc(width, sizeof(bool));
	}

	flood_fill(startX, startY, map, visited, width, height, &exitFound, &itemsLeft);

	for (int j = 0; j < height; j++)
	{
		free(visited[j]);
	}
	free(visited);

	// Возвращаем true, если найден выход и все предметы собраны
	return exitFound && itemsLeft == 0;
}
