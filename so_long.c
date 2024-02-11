/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 14:02:23 by edouard           #+#    #+#             */
/*   Updated: 2024/02/11 13:18:16 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int keypress_count = 0;

int game_loop(t_game_state *game_state)
{
	static clock_t last_update = 0;
	clock_t current_time = clock();

	if ((current_time - last_update) > CLOCKS_PER_SEC / 25) // La frecuencia de actualización es de 25 FPS
	{
		mlx_clear_window(game_state->data->mlx_ptr, game_state->data->win_ptr);									 // Netoyage de la fenêtre
		ft_put_textures(game_state->data, &game_state->game_map, game_state->sheep, game_state->player); // Re-affichage des textures

		// Mise à jour des animations
		updateSheepAnimation(game_state->sheep, 2, 4);
		if (game_state->player->is_moving)
			updatePlayerAnimation(game_state->player, 4);
		else
			game_state->player->current_sprite = 0;

		last_update = current_time;
	}

	return (0);
}

int on_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

int on_keypress(int keysym, t_game_state *data)
{
	printf("Keypress #%d: %d\n", ++keypress_count, keysym);
	handle_player_movement(keysym, data->player, data->game_map);
	return (0);
}

int main(int argc, char **argv)
{
	int fd;
	t_game_map *game_map;
	t_data data;
	t_sheep *sheep;
	t_player *player;
	t_game_state *game_state;

	game_state = malloc(sizeof(t_game_state));
	if (!game_state)
		print_errors("Error: Memory allocation failed for game_state\n");

	sheep = malloc(sizeof(t_sheep));
	if (!sheep)
	{
		free(game_state);
		print_errors("Error: Memory allocation failed for sheep\n");
	}

	game_map = NULL;

	// Verifier comment libere la memoire de mlx_ptr
	data.mlx_ptr = mlx_init();

	if (!data.mlx_ptr)
	{
		free(game_state);
		free(sheep);
		// voir si il faut mlx_destroy_window
		print_errors("Error: MLX initialization failed\n");
	}

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		free(game_state);
		free(sheep);
		print_errors("Error: File not found\n");
	}

	if (check_params(argc, argv, fd))
		init_game_map(fd, &game_map, argv[1]);

	data.win_ptr = mlx_new_window(data.mlx_ptr, game_map->map_length * 31.3, game_map->map_height * 33, "So Long");

	if (!data.win_ptr)
	{
		free_game_map(&game_map);
		free(data.mlx_ptr);
		mlx_destroy_window(data.mlx_ptr, data.win_ptr);
		exit(1);
	}

	init_player(&player, &data, &game_map);

	load_map(&data, &game_map, sheep, player);

	if (sheep == NULL || game_map == NULL)
	{
		free(game_state);
		return (free(data.mlx_ptr), 1);
	}
	(*game_state).data = &data;
	(*game_state).game_map = game_map;
	(*game_state).sheep = sheep;
	(*game_state).player = player;
	// Register keypress hook
	mlx_hook(data.win_ptr, 2, 1L << 0, &on_keypress, game_state);

	// Register destroy hook
	mlx_hook(data.win_ptr, 17, 1L << 4, &on_destroy, &data);

	// Loop over the MLX pointer
	mlx_loop_hook(data.mlx_ptr, &game_loop, game_state);
	mlx_loop(data.mlx_ptr);

	return (1);
}
