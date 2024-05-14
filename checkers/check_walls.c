/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:30:11 by edouard           #+#    #+#             */
/*   Updated: 2024/05/14 17:12:28 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	check_first_line(char *line)
{
	int	i;
	int	length;

	i = 0;
	length = ft_strlen(line);
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

static int	check_mediums_lines(char *line)
{
	int	i;
	int	length;

	i = 0;
	length = ft_strlen(line);
	
	if (line[length - 1] == '\n')
		length--;

	if (line[0] != '1' || line[length - 1] != '1')
		return (0);
	while (i < length)
	{
		if (line[i] != 'C' && line[i] != 'P' && line[i] != 'E' && line[i] != '0'
			&& line[i] != '1' && line[i] != 'N')
			return (0);
		i++;
	}
	return (1);
}

static int	check_last_line(char *line)
{
	int	i;
	int	length;

	i = 0;
	length = ft_strlen(line);

	while (i < length - 1)
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

static void make_gnl(char *line)
{
	int fd;
	fd = open("./maps/map_empty.ber", O_RDONLY);
	get_next_line(fd);
	free(line);

}

int	check_walls(char *line, int line_type, t_resources *res)
{
	if (line_type == 1 && !check_first_line(line))
		{
			make_gnl(line);
			free_resources(res);
			print_errors("First line is not valid");
		}	
	else if (line_type == 3 && !check_last_line(line))
		{
			make_gnl(line);
			free_resources(res);
			print_errors("Last line is not valid");
		}
	else if (line_type == 2 && !check_mediums_lines(line))
		{
			make_gnl(line);
			free_resources(res);
			print_errors("Medium line is not valid");
		}
	return (1);
}

