#ifndef SO_LONG_H
#define SO_LONG_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <time.h>

#include "mlx/mlx.h"
#include "libft/libft.h"
#include "printf/ft_printf.h"
#include "gnl/get_next_line.h"

// STRUCTS

typedef struct s_player
{
	int x;
	int y;
	int prev_x;
	int prev_y;
	void **sprites_up;
	void **sprites_down;
	void **sprites_left;
	void **sprites_right;
	int current_sprite;
	clock_t last_update;
	int frame_count;
	bool is_moving;
	char direction;
	int steps;
} t_player;

typedef struct s_enemy
{
	int x;
	int y;
	int prev_x;
	int prev_y;
	void **sprites;
	int current_sprite;
	clock_t last_update;
	int frame_count;
	bool is_moving;
} t_enemy;

typedef struct s_pos
{
	int x;
	int y;
} t_pos;

typedef struct s_sheep
{
	int x;
	int y;
	void **sprites;
	int current_sprite;
	clock_t last_update;
	int frame_count;
	bool is_collected;
} t_sheep;

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
	void *end_img;
	void *wall;
	void *wall_map;
	void *exit;
	t_player player;
	void *floor;
	t_sheep *sheep;
	void *enemy;
	int usual_texture_width;
	int usual_texture_height;
} t_game_map;

typedef struct s_render_v
{
	void *mlx_ptr;
	void *win_ptr;
} t_data;

typedef struct s_resources
{
	t_game_map *game_map;
	t_data data;
	t_sheep *sheep;
	t_player *player;
	t_enemy *enemy;
	int enemy_count;
	int sheep_count;
} t_resources;

// INITIALIZERS MAP ARRAY
t_game_map **init_game_map(int fd, t_resources *resources, char *file_path);
void free_game_map(t_game_map **all_map);
void free_resources(t_resources *res);
void init_resources_and_mlx(t_resources *res);
void setup_game_environment(t_resources *res, int argc, char **argv);
void display_steps(t_resources *resources);
void end_game(t_resources *res, int win);
void set_player_position(t_resources *res);

// CHECKERS
int check_params(int argc, char **argv, int fd);
void print_errors(char *error);
int check_walls(char *line, int line_type);
int check_rectangular(char *line);
int check_game(char *line);
void reset_game_checks();
bool check_path_exists(char **map, int width, int height, int startX, int startY, int itemsCount);

// HOOKS
int on_destroy(t_resources *res);
int on_keypress(int keysym, t_resources *data);

// LOADERS AND DRAWERS MAP
void load_map(t_resources *res);
void read_and_process_lines(int fd, t_resources *resources, int num_of_lines);
void ft_load_textures(t_resources *res);
void ft_put_textures(t_resources *res);
void ft_free_textures(t_resources *res);

// LOADERS AND DRAWERS LAYERS
void ft_load_first_layer(t_resources *res);
void ft_load_second_layer(t_resources *res);
void ft_load_three_layer(t_resources *res);

// SHEEP FUNCTIONS
void init_and_load_sheep(t_resources *res);
void drawSheep(t_data *data, t_sheep *sheep);
void updateSheepAnimation(t_sheep *sheep, int interval, int sprite_count);
void sheep_draw_layer(t_resources *res, int y, int x);
void sheep_count(t_resources *res);

// PLAYER FUNCTIONS
void upload_player_sprites(t_resources *s_resources);
void init_player(t_resources *resources);
void drawPlayer(t_resources *resources);
void handle_player_movement(int keysym, t_resources *res);
void updatePlayerAnimation(t_player *player, int interval);
void free_player(t_player *player);
void player_draw_layer(t_resources *res, int y, int x);

// ENEMY FUNCTIONS
void init_enemy(t_resources *resources);
void drawEnemy(t_resources *resources, t_enemy *enemy);
void updateEnemyPatrol(t_resources *resources);
void updateEnemyAnimation(t_enemy *enemy, int interval);
void upload_enemy_sprite(t_resources *resources, t_enemy *enemy, int index);
void free_enemys_sprites(t_resources *res);
void init_enemy_positions(t_resources *resources, t_pos *available_positions, int available_positions_count);
t_pos *get_available_positions_for_enemies(t_resources *resources, int *available_positions_count);
#endif