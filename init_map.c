/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:42:39 by edouard           #+#    #+#             */
/*   Updated: 2024/01/25 11:58:36 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int count_lines(int fd)
{
	char *line;
	int num_of_lines = 0;
	while ((line = get_next_line(fd)) != NULL)
		num_of_lines++;
	return num_of_lines;
}

t_game_map **init_game_map(int fd, t_game_map **all_map)
{
	char *line;
	int num_of_lines = count_lines(fd);
	*all_map = malloc(sizeof(t_game_map));
	if (!*all_map)
		return NULL;
	(*all_map)->map_data = malloc(sizeof(char *) * num_of_lines);
	if (!(*all_map)->map_data)
	{
		free(*all_map);
		return NULL;
	}
	int current_line = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (check_rectangular(line) && check_walls(line) && check_game(line))
		{
			init_array(line, all_map, current_line);
			current_line++;
		}
		free(line);
		num_of_lines++;
	}

	return all_map;
}

void init_array(char *line, t_game_map **map, int current_line)
{
	// Выделяем память для одной строки карты
	(*map)->map_data[current_line] = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!(*map)->map_data[current_line])
	{
		// Обработка ошибки выделения памяти
		return;
	}

	// Копируем содержимое line в map_data, используя ft_strlcpy
	ft_strlcpy((*map)->map_data[current_line], line, ft_strlen(line) + 1);
}
