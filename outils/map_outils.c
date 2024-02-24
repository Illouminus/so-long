/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_outils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 11:48:08 by edouard           #+#    #+#             */
/*   Updated: 2024/02/24 17:18:23 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	free_game_map(t_game_map **all_map)
{
	int	i;

	if (all_map != NULL && *all_map != NULL)
	{
		if ((*all_map)->map_data != NULL)
		{
			i = 0;
			while ((*all_map)->map_data[i] != NULL)
			{
				free((*all_map)->map_data[i]);
				i++;
			}
			free((*all_map)->map_data);
		}
		free(*all_map);
		*all_map = NULL;
	}
}

static void	init_array(char *line, t_resources *resources, int current_line)
{
	resources->game_map->map_data[current_line] = ft_strdup(line);
	if (!resources->game_map->map_data[current_line])
	{
		free_resources(resources);
		print_errors("Erreur d'allocation mémoire");
	}
}

static int	process_line(char *line, t_resources *resources, int num_of_lines,
		int current_line)
{
	int	line_type;

	if (current_line == 0)
	{
		resources->game_map->map_length = ft_strlen(line);
		line_type = 1;
	}
	else if (current_line == num_of_lines - 1)
		line_type = 3;
	else
		line_type = 2;
	if (line_type == 2 && !check_game(line))
		free_resources(resources);
	if (check_rectangular(line) && check_walls(line, line_type))
		init_array(line, resources, current_line);
	return (1);
}

static void	init_map_const(t_resources *resources, int num_of_lines)
{
	resources->game_map->map_height = num_of_lines;
	resources->game_map->map_length = -1;
	resources->game_map->usual_texture_height = 64;
	resources->game_map->usual_texture_width = 64;
	resources->game_map->floor = NULL;
	resources->game_map->wall = NULL;
	resources->game_map->wall_map = NULL;
	resources->game_map->exit = NULL;
}

void	read_and_process_lines(int fd, t_resources *resources, int num_of_lines)
{
	char	*line;
	int		current_line;

	current_line = 0;
	init_map_const(resources, num_of_lines);
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			break ;
		}
		if (!process_line(line, resources, num_of_lines, current_line))
		{
			free(line);
			close(fd);
			return ;
		}
		free(line);
		current_line++;
	}
	close(fd);
}
