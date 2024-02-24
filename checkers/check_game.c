/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:49:18 by ebaillot          #+#    #+#             */
/*   Updated: 2024/02/24 17:14:22 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	g_player_presence = 0;
static int	g_exit_presence = 0;
static int	g_collectible_presence = 0;

void	reset_game_checks(void)
{
	g_player_presence = 0;
	g_exit_presence = 0;
	g_collectible_presence = 0;
}

static int	check_player_presence(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'P')
		{
			g_player_presence++;
		}
		i++;
	}
	return (g_player_presence <= 1);
}

static int	check_exit_presence(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'E')
		{
			g_exit_presence++;
		}
		i++;
	}
	return (g_exit_presence <= 1);
}

static int	check_collectibles_presence(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'C')
		{
			g_collectible_presence++;
		}
		i++;
	}
	return (g_collectible_presence > 0);
}

int	check_game(char *line)
{
	if (!check_player_presence(line))
		print_errors("More than one player on map.");
	if (!check_exit_presence(line))
		print_errors("More than one exit on map.");
	if (!check_collectibles_presence(line))
		print_errors("No collectibles on map.");
	return (1);
}
