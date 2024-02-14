/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_route.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 20:51:00 by edouard           #+#    #+#             */
/*   Updated: 2024/02/14 10:22:34 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void flood_fill(int x, int y, char **map, bool **visited, int width, int height, bool *exitFound, int *itemsLeft)
{
	if (x < 0 || x >= width || y < 0 || y >= height || visited[y][x] || map[y][x] == '1')
		return;

	visited[y][x] = true;

	if (map[y][x] == 'E' && *itemsLeft == 0)
	{
		*exitFound = true;
		return;
	}

	if (map[y][x] == 'C')
	{
		(*itemsLeft)--;
	}

	flood_fill(x + 1, y, map, visited, width, height, exitFound, itemsLeft);
	flood_fill(x - 1, y, map, visited, width, height, exitFound, itemsLeft);
	flood_fill(x, y + 1, map, visited, width, height, exitFound, itemsLeft);
	flood_fill(x, y - 1, map, visited, width, height, exitFound, itemsLeft);
}

bool check_path_exists(char **map, int width, int height, int startX, int startY, int itemsCount)
{
	bool exitFound = false;
	int itemsLeft = itemsCount;
	bool **visited = malloc(height * sizeof(bool *));
	int i;
	int j;

	i = 0;
	while (i < height)
	{
		visited[i] = ft_calloc(width, sizeof(bool));
		i++;
	}

	flood_fill(startX, startY, map, visited, width, height, &exitFound, &itemsLeft);
	j = 0;
	while (j < height)
	{
		free(visited[j]);
		j++;
	}
	free(visited);

	return exitFound && itemsLeft == 0;
}
