/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:26:53 by edouard           #+#    #+#             */
/*   Updated: 2024/01/28 11:05:35 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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

int check_rectangular(char *line)
{
	static size_t first_line_length = 0;
	size_t current_line_length = ft_strlen(line);
	if (current_line_length > 0 && line[current_line_length - 1] == '\n')
		current_line_length--;
	if (first_line_length == 0)
		first_line_length = current_line_length;
	else if (current_line_length != first_line_length)
		print_errors("Map is not rectangular");
	return (current_line_length);
}

void print_errors(char *error)
{
	ft_printf("Error\n%s\n", error);
	exit(1);
}
