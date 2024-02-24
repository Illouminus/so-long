/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 14:02:23 by edouard           #+#    #+#             */
/*   Updated: 2024/02/24 15:22:50 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	keypress_count = 0;

int	game_loop(t_resources *resources)
{
	clock_t			current_time;
	static clock_t	last_update = 0;

	current_time = clock();
	if ((current_time - last_update) > CLOCKS_PER_SEC / 5)
	{
		mlx_clear_window(resources->data.mlx_ptr, resources->data.win_ptr);
		ft_put_textures(resources);
		updateSheepAnimation(resources->sheep, 2, 4);
		if (resources->player->is_moving)
			updatePlayerAnimation(resources->player, 4);
		else
			resources->player->current_sprite = 0;
		if (resources->enemy_count > 0)
			updateEnemyPatrol(resources);
		updateEnemyAnimation(&resources->enemy[0], 8);
		updateEnemyAnimation(&resources->enemy[1], 8);
		updateEnemyAnimation(&resources->enemy[2], 8);
		updateEnemyAnimation(&resources->enemy[3], 8);
		display_steps(resources);
		last_update = current_time;
	}
	return (0);
}

int	on_destroy(t_resources *res)
{
	free_resources(res);
	exit(0);
	return (0);
}

int	on_keypress(int keysym, t_resources *data)
{
	if (keysym == 65307)
		end_game(data, 0);
	handle_player_movement(keysym, data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_resources	res;

	ft_bzero(&res, sizeof(t_resources));
	init_resources_and_mlx(&res);
	setup_game_environment(&res, argc, argv);
	mlx_hook(res.data.win_ptr, 2, 1L << 0, &on_keypress, &res);
	mlx_hook(res.data.win_ptr, 17, 1L << 4, &on_destroy, &res);
	mlx_loop_hook(res.data.mlx_ptr, &game_loop, &res);
	mlx_loop(res.data.mlx_ptr);
	free_resources(&res);
	return (0);
}
