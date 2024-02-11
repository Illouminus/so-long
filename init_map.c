/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:42:39 by edouard           #+#    #+#             */
/*   Updated: 2024/02/11 12:05:07 by edouard          ###   ########.fr       */
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

t_game_map **init_game_map(int fd, t_game_map **all_map, char *file_path)
{
	int num_of_lines = count_lines(fd);
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

	reset_game_checks();
	read_and_process_lines(fd, all_map, num_of_lines);

	return all_map;
}
