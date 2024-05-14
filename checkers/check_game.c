/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:49:18 by ebaillot          #+#    #+#             */
/*   Updated: 2024/03/18 16:36:59 by ebaillot         ###   ########.fr       */
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

void	check_player_presence(char *line)
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
}

void	check_exit_presence(char *line)
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
}

void	check_collectibles_presence(char *line)
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
}

void	validate_map(t_resources *res)
{
	if (g_player_presence != 1)
	{
		free_resources(res);
		print_errors("More than one player on map or not player found.");
	}
	if (g_exit_presence < 1 || g_exit_presence > 1)
	{
		free_resources(res);
		print_errors("More than one exit on map or not exit found.");
	}
	if (g_collectible_presence < 1)
	{
		free_resources(res);
		print_errors("No collectibles on map.");
	}
		
}
