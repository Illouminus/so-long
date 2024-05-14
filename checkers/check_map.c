/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:26:53 by edouard           #+#    #+#             */
/*   Updated: 2024/03/18 16:06:08 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	check_file_extension(const char *filename, const char *extension)
{
	const char	*dot;

	dot = ft_strrchr(filename, '.');
	if (!dot || dot == filename)
		return (0);
	return (ft_strcmp(dot, extension) == 0);
}

int	check_params(int argc, char **argv, int fd)
{
	if (argc != 2)
		print_errors("Wrong number of arguments");
	if (!check_file_extension(argv[1], ".ber"))
		print_errors("Wrong file extension");
	if (fd == -1)
		print_errors("File not found");
	return (1);
}

int	check_rectangular(char *line, t_resources *res)
{
	static size_t	first_line_length = 0;
	size_t			current_line_length;

	current_line_length = ft_strlen(line);
	if (current_line_length > 0 && line[current_line_length - 1] == '\n')
		current_line_length--;
	if (first_line_length == 0)
		first_line_length = current_line_length;
	else if (current_line_length != first_line_length)
		{
			free(line);
			free_resources(res);
			print_errors("Map is not rectangular");
		}
		
	return (current_line_length);
}

void	print_errors(char *error)
{
	ft_printf("Error\n%s\n", error);
	exit(1);
}

int	check_game(char *line)
{
	check_player_presence(line);
	check_exit_presence(line);
	check_collectibles_presence(line);
	return (1);
}
