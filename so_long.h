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
	void *mlx_ptr;
	void *win_ptr;
} t_data;

t_game_map **init_game_map(int fd, t_game_map **all_map, char *file_path);
void init_array(char *line, t_game_map **map, int current_line);
void free_game_map(t_game_map **all_map, int num_lines);

// CHECKERS
int check_params(int argc, char **argv, int fd);
void print_errors(char *error);
int check_walls(char *line, int line_type);
int check_rectangular(char *line);
int check_game(char *line);
void reset_game_checks();

int on_destroy(t_data *data);
int on_keypress(int keysym, t_data *data);
#endif