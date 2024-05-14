/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:42:39 by edouard           #+#    #+#             */
/*   Updated: 2024/03/18 15:54:25 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_lines(int fd)
{
	char	*line;
	int		num_of_lines;

	num_of_lines = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		num_of_lines++;
		free(line);
		line = get_next_line(fd);
	}
	return (num_of_lines);
}

void	init_next_part(t_resources *resources, int num_of_lines, int fd)
{
	bool	is_check;
	

	reset_game_checks();
	init_array_null((void **)resources->game_map->map_data, num_of_lines);
	read_and_process_lines(fd, resources, num_of_lines);
	sheep_count(resources);
	set_player_position(resources);
	validate_map(resources);
	is_check = check_path_exists(resources->game_map, resources->sheep_count);
	if (!is_check)
	{
		free_resources(resources);
		print_errors("Error: Map has no valid exit\n");
	}
}

t_game_map	**init_game_map(int fd, t_resources *resources, char *file_path)
{
	int	num_of_lines;

	num_of_lines = count_lines(fd);
	if (num_of_lines < 3)
	{
		free_resources(resources);
		print_errors("Error: Map is not valid\n");
	}
	close(fd);
	fd = open(file_path, O_RDONLY);
	resources->game_map = malloc(sizeof(t_game_map));
	if (!resources->game_map)
	{
		free_resources(resources);
		print_errors("Error: Memory allocation failed for game_map\n");
	}
	resources->game_map->map_data = ft_calloc(sizeof(char *), num_of_lines + 1);
	if (!resources->game_map->map_data)
	{
		free_resources(resources);
		print_errors("Error: Memory allocation failed for map_data\n");
	}
	init_next_part(resources, num_of_lines, fd);
	return (&resources->game_map);
}
