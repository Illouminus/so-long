/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 14:02:23 by edouard           #+#    #+#             */
/*   Updated: 2024/01/28 19:21:05 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int game_loop(t_game_state *game_state)
{
	static clock_t last_update = 0;
	clock_t current_time = clock();
	// Если прошло достаточно времени с последнего обновления
	if ((current_time - last_update) > CLOCKS_PER_SEC / 25) // 60 раз в секунду
	{
		mlx_clear_window(game_state->data->mlx_ptr, game_state->data->win_ptr);		  // Очистка экрана
		ft_put_textures(game_state->data, &game_state->game_map, game_state->sheep); // Перерисовка всех слоев

		// Обновляем анимацию овцы
		updateSheepAnimation(game_state->sheep, 2, 4); // Вставьте здесь нужные параметры

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

int on_keypress(int keysym, t_data *data)
{
	printf("Pressed key: %d\\n", keysym);
	return (0);
}

int main(int argc, char **argv)
{
	int fd;
	t_game_map *game_map;
	t_data data;
	t_sheep *sheep;
	t_game_state *game_state = malloc(sizeof(t_game_state));
	if (!game_state)
	{
		// Обработка ошибки выделения памяти
		fprintf(stderr, "Error: Failed to allocate memory for game state\n");
		return (free(data.mlx_ptr), 1);
	}

	sheep = malloc(sizeof(t_sheep));
	game_map = NULL;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (check_params(argc, argv, fd))
		init_game_map(fd, &game_map, argv[1]);

	data.win_ptr = mlx_new_window(data.mlx_ptr, game_map->map_length * 31.3, game_map->map_height * 33, "So Long");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);

	load_map(&data, &game_map, sheep);
	if (sheep == NULL || game_map == NULL)
	{
		free(game_state);
		return (free(data.mlx_ptr), 1);
	}
	(*game_state).data = &data;
	(*game_state).game_map = game_map;
	(*game_state).sheep = sheep;
	// Register keypress hook
	mlx_hook(data.win_ptr, 2, 1L << 0, &on_keypress, &data);

	// Register destroy hook
	mlx_hook(data.win_ptr, 17, 1L << 4, &on_destroy, &data);

	// Loop over the MLX pointer
	mlx_loop_hook(data.mlx_ptr, &game_loop, game_state);
	mlx_loop(data.mlx_ptr);

	return (1);
}