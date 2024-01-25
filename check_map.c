/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:42:39 by edouard           #+#    #+#             */
/*   Updated: 2024/01/25 08:28:07 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int check_params(int argc, char **argv, int fd)
{
	if (argc != 2)
		print_errors("Wrong number of arguments");
	if (!ft_strncmp(argv[1], ".ber", 4))
		print_errors("Wrong file extension");
	if (fd == -1)
		print_errors("File not found");
	return (1);
}

t_game_map **init_game_map(int fd, t_game_map **map_data)
{
	char *line;
	int is_last_line = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Read line: %s\n", line);
		printf("Line length: %zu\n", ft_strlen(line));
		if (line + 1 == NULL)
			is_last_line = 1;

		check_walls(line);
		check_length(line, is_last_line);
	}

	return map_data;
}

int check_length(char *line, int is_last_line)
{
	static size_t first_line = 0;
	size_t length = 0;
	printf("Last line: %d\n", is_last_line);
	if (is_last_line)
		length += 1;
	if (first_line == 0)
		first_line = ft_strlen(line);
	length = ft_strlen(line);

	if (ft_strlen(line) != first_line)
		print_errors("Map is not rectangular");
	return (length);
}

int check_walls(char *line)
{
	static char *first_line;
}

void print_errors(char *error)
{
	ft_printf("Error\n%s\n", error);
	exit(1);
}