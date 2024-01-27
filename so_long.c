/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 14:02:23 by edouard           #+#    #+#             */
/*   Updated: 2024/01/27 09:11:25 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int on_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

int on_keypress(int keysym, t_data *data)
{
	(void)data;
	printf("Pressed key: %d\\n", keysym);
	return (0);
}

int main(int argc, char **argv)
{
	int fd;
	t_game_map *game_map;
	t_data data;
	game_map = NULL;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1000, 700, "1000x700");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);
	fd = open(argv[1], O_RDONLY);
	if (check_params(argc, argv, fd))
		init_game_map(fd, &game_map, argv[1]);

	mlx_hook(data.win_ptr, 2, 1L << 0, &on_keypress, &data);

	// Register destroy hook
	mlx_hook(data.win_ptr, 17, 1L << 4, &on_destroy, &data);

	// Loop over the MLX pointer
	mlx_loop(data.mlx_ptr);
	return (1);
}