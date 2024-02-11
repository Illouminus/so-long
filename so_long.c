/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 14:02:23 by edouard           #+#    #+#             */
/*   Updated: 2024/02/11 20:44:37 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int keypress_count = 0;

int game_loop(t_resources *resources)
{
	static clock_t last_update = 0;
	clock_t current_time = clock();

	if ((current_time - last_update) > CLOCKS_PER_SEC / 25) // La frecuencia de actualización es de 25 FPS
	{
		mlx_clear_window(resources->data.mlx_ptr, resources->data.win_ptr); // Netoyage de la fenêtre
		ft_put_textures(resources);													  // Re-affichage des textures

		// Mise à jour des animations
		updateSheepAnimation(resources->sheep, 2, 4);
		if (resources->player->is_moving)
			updatePlayerAnimation(resources->player, 4);
		else
			resources->player->current_sprite = 0;

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

int on_keypress(int keysym, t_resources *data)
{
	printf("Keypress #%d: %d\n", ++keypress_count, keysym);
	handle_player_movement(keysym, data->player, data->game_map);
	return (0);
}

int main(int argc, char **argv)
{
	t_resources res;
	ft_bzero(&res, sizeof(t_resources));

	init_resources_and_mlx(&res);
	setup_game_environment(&res, argc, argv);

	mlx_hook(res.data.win_ptr, 2, 1L << 0, &on_keypress, &res);
	mlx_hook(res.data.win_ptr, 17, 1L << 4, &on_destroy, &res.data);
	mlx_loop_hook(res.data.mlx_ptr, &game_loop, &res);
	mlx_loop(res.data.mlx_ptr);

	free_resources(&res);
	return 0;
}
