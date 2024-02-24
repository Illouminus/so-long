/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:46:07 by edouard           #+#    #+#             */
/*   Updated: 2024/02/24 16:04:19 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	upload_enemy_sprites(t_resources *resources, int enemy_index)
{
	t_enemy	*current_enemy;
	int		i;

	current_enemy = &resources->enemy[enemy_index];
	i = 0;
	while (i < current_enemy->frame_count)
	{
		upload_enemy_sprite(resources, current_enemy, i);
		i++;
	}
}

void	init_one_enemy(t_enemy *enemy, t_resources *resources)
{
	enemy->current_sprite = 0;
	enemy->last_update = clock();
	enemy->frame_count = 8;
	enemy->is_moving = false;
	enemy->sprites = malloc(sizeof(void *) * enemy->frame_count);
	if (!enemy->sprites)
	{
		free_resources(resources);
		print_errors("Malloc error in enemy sprites allocation\n");
	}
}

t_pos	*get_and_validate_positions(t_resources *resources,
		int *available_positions_count)
{
	t_pos	*available_positions;

	available_positions = get_available_positions_for_enemies(resources,
			available_positions_count);
	if (!available_positions
		|| *available_positions_count < resources->enemy_count)
		print_errors("Not enough space for enemies\n");
	return (available_positions);
}

void	init_and_setup_enemies(t_resources *resources,
		t_pos *available_positions, int available_positions_count)
{
	int	i;

	resources->enemy = malloc(sizeof(t_enemy) * resources->enemy_count);
	if (!resources->enemy)
		print_errors("Malloc error in init enemy function\n");
	init_enemy_positions(resources, available_positions,
		available_positions_count);
	i = 0;
	while (i < resources->enemy_count)
	{
		init_one_enemy(&(resources->enemy[i]), resources);
		upload_enemy_sprites(resources, i);
		i++;
	}
}

void	init_enemy(t_resources *resources)
{
	int		available_positions_count;
	t_pos	*available_positions;

	available_positions_count = 0;
	resources->enemy_count = 4;
	available_positions = get_and_validate_positions(resources,
			&available_positions_count);
	init_and_setup_enemies(resources, available_positions,
		available_positions_count);
	free(available_positions);
}
