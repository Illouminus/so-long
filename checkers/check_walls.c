/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:30:11 by edouard           #+#    #+#             */
/*   Updated: 2024/01/28 11:06:31 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int check_first_line(char *line)
{
	int i = 0;
	int length = ft_strlen(line);

	if (line[length - 1] == '\n')
	{
		length--;
	}

	while (i < length)
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int check_mediums_lines(char *line)
{
	int i = 1;
	int length = ft_strlen(line);

	if (line[length - 1] == '\n')
		length--;
	if (line[0] != '1' || line[length - 1] != '1')
		return (0);
	while (i < length - 1)
	{
		if (line[i] != 'C' && line[i] != 'P' && line[i] != 'E' && line[i] != '0' && line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int check_last_line(char *line)
{
	int i = 0;
	while (line[i])
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int check_walls(char *line, int line_type)
{
	if (line_type == 1 && !check_first_line(line))
		print_errors("First line is not valid");
	else if (line_type == 3 && !check_last_line(line))
		print_errors("Last line is not valid");
	else if (line_type == 2 && !check_mediums_lines(line))
		print_errors("Medium line is not valid");

	return (1);
}
