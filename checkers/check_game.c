/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:31:48 by edouard           #+#    #+#             */
/*   Updated: 2024/01/25 10:22:44 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int check_player_presence(char *line)
{
	int i;
	static int player_presence = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 'P')
			player_presence++;
		i++;
	}
	if (player_presence > 1)
		return (0);
	return (1);
}

static int check_exit_presence(char *line)
{
	int i;
	static int exit_presence = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 'E')
			exit_presence++;
		i++;
	}
	if (exit_presence > 1)
		return (0);
	return (1);
}

static int check_collectibles_presence(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'C')
			return (1);
		i++;
	}
	return (0);
}

int check_game(char *line)
{
	if (!check_player_presence(line))
		print_errors("You have to check your player presence on map.");
	if (!check_exit_presence(line))
		print_errors("You have to check your exit presence on map.");
	if (!check_collectibles_presence(line))
		print_errors("You have to check your collectibles presence on map.");
	return (1);
}