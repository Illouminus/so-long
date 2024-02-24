#include "../so_long.h"

static int	player_presence = 0;
static int	exit_presence = 0;
static int	collectible_presence = 0;

void	reset_game_checks(void)
{
	player_presence = 0;
	exit_presence = 0;
	collectible_presence = 0;
}

static int	check_player_presence(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'P')
		{
			player_presence++;
		}
		i++;
	}
	return (player_presence <= 1);
}

static int	check_exit_presence(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'E')
		{
			exit_presence++;
		}
		i++;
	}
	return (exit_presence <= 1);
}

static int	check_collectibles_presence(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'C')
		{
			collectible_presence++;
		}
		i++;
	}
	return (collectible_presence > 0);
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
