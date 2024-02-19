/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:42:39 by edouard           #+#    #+#             */
/*   Updated: 2024/02/19 22:02:27 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Returns the number of lines in the file
static int count_lines(int fd)
{
	char *line;
	int num_of_lines = 0;
	while ((line = get_next_line(fd)) != NULL)
		num_of_lines++;
	return num_of_lines;
}

void init_next_part(t_resources *resources, int num_of_lines, int fd)
{
	reset_game_checks();
	init_array_null((void **)resources->game_map->map_data, num_of_lines);
	read_and_process_lines(fd, resources, num_of_lines);
	sheep_count(resources);
	set_player_position(resources);

	bool isCheck = check_path_exists(resources->game_map->map_data, resources->game_map->map_length,
												resources->game_map->map_height, resources->game_map->player_position_x,
												resources->game_map->player_position_y, resources->sheep_count);
	if (!isCheck)
	{
		free_resources(resources);
		print_errors("Error: Map has no valid exit\n");
	}
}

t_game_map **init_game_map(int fd, t_resources *resources, char *file_path)
{
	int num_of_lines = count_lines(fd);
	close(fd);
	fd = open(file_path, O_RDONLY);

	resources->game_map = malloc(sizeof(t_game_map));
	if (!resources->game_map)
	{
		free_resources(resources);
		print_errors("Error: Memory allocation failed for game_map\n");
	}

	resources->game_map->map_data = malloc(sizeof(char *) * num_of_lines + 1);
	if (!resources->game_map->map_data)
	{
		free_resources(resources);
		print_errors("Error: Memory allocation failed for map_data\n");
	}
	init_next_part(resources, num_of_lines, fd);
	return &resources->game_map;
}
