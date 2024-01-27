/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:42:39 by edouard           #+#    #+#             */
/*   Updated: 2024/01/27 16:56:38 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_game_map(t_game_map **all_map, int num_lines)
{
	if (all_map != NULL && *all_map != NULL)
	{
		int i = 0;
		while (i < num_lines && (*all_map)->map_data[i] != NULL)
		{
			free((*all_map)->map_data[i]);
			i++;
		}
		free((*all_map)->map_data);
		free(*all_map);
	}
}

int count_lines(int fd)
{
	char *line;
	int num_of_lines = 0;
	while ((line = get_next_line(fd)) != NULL)
		num_of_lines++;
	return num_of_lines;
}

t_game_map **init_game_map(int fd, t_game_map **all_map, char *file_path)
{
	char *line;
	int num_of_lines = count_lines(fd);
	int line_type;

	close(fd);
	fd = open(file_path, O_RDONLY);

	*all_map = malloc(sizeof(t_game_map));

	if (!*all_map)
		return NULL;

	(*all_map)->map_data = malloc(sizeof(char *) * num_of_lines);

	if (!(*all_map)->map_data)
	{
		free(*all_map);
		return NULL;
	}
	(*all_map)->map_height = num_of_lines;
	(*all_map)->map_length = 0;
	(*all_map)->usual_texture_height = 32;
	(*all_map)->usual_texture_width = 32;

	reset_game_checks();
	int current_line = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (current_line == 0)
			(*all_map)->map_length = ft_strlen(line);
		line_type = (current_line == 0) ? 1 : ((current_line == num_of_lines - 1) ? 3 : 2);
		if (line_type == 2 && !check_game(line))
		{
			free_game_map(all_map, current_line);
			print_errors("Error in game map");
			free(line);
			return NULL;
		}
		if (check_rectangular(line) && check_walls(line, line_type))
		{
			init_array(line, all_map, current_line);
			current_line++;
		}
		free(line);
	}

	return all_map;
}

void init_array(char *line, t_game_map **map, int current_line)
{
	// Выделяем память для одной строки карты
	(*map)->map_data[current_line] = ft_strdup(line);
	if (!(*map)->map_data[current_line])
	{
		// Обработка ошибки выделения памяти
		return;
	}
}
