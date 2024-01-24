#ifndef SO_LONG_H
#define SO_LONG_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "mlx/mlx.h"
#include "libft/libft.h"
#include "printf/ft_printf.h"
#include "gnl/get_next_line.h"

typedef struct s_game_map
{
	int map_height;
	int map_length;
	int player_position_x;
	int player_position_y;
	int game_score;
	int max_score;
	char **map_data;
	int game_over;
	int steps;
	void *end_img;
	void *wall;
	void *exit;
	void *player;
	void *floor;
	void *items;
	void *enemy;
	int *enemypos;
} t_game_map;

typedef struct s_render_v
{
	void *mlx;
	void *win;
} t_render_v;

int check_params(int argc, char **argv, int fd);
void print_errors(char *error);

t_game_map **init_game_map(int fd, t_game_map **map_data);

int check_walls(char *line);
int check_length(char *line, int is_last_line);

#endif