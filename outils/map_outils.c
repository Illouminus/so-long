/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_outils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 11:48:08 by edouard           #+#    #+#             */
/*   Updated: 2024/02/13 22:14:26 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void free_game_map(t_game_map **all_map)
{
	if (all_map != NULL && *all_map != NULL)
	{
		if ((*all_map)->map_data != NULL)
		{
			int i = 0;
			while ((*all_map)->map_data[i] != NULL)
			{
				free((*all_map)->map_data[i]);
				i++;
			}
			free((*all_map)->map_data);
		}

		free(*all_map);
		*all_map = NULL;
	}
}

// Initialise un tableau avec la ligne de la carte
static void init_array(char *line, t_resources *resources, int current_line)
{
	resources->game_map->map_data[current_line] = ft_strdup(line);
	if (!resources->game_map->map_data[current_line])
	{
		free_resources(resources);
		print_errors("Erreur d'allocation mémoire");
	}
}

// Traite une ligne individuelle de la carte
static int process_line(char *line, t_resources *resources, int num_of_lines, int current_line)
{
	int line_type;

	if (current_line == 0)
	{
		resources->game_map->map_length = ft_strlen(line);
		line_type = 1; // Type de ligne pour l'en-tête
	}
	else if (current_line == num_of_lines - 1)
		line_type = 3; // Type de ligne pour le pied
	else
		line_type = 2; // Type de ligne pour le corps

	if (line_type == 2 && !check_game(line))
	{
		// En cas d'erreur dans la vérification du jeu, libérer la carte et signaler une erreur
		free_game_map(&resources->game_map);
		print_errors("Erreur dans la carte du jeu");
		return 0;
	}
	if (check_rectangular(line) && check_walls(line, line_type))
		init_array(line, resources, current_line);
	return 1; // Succès
}

// Initialise les constantes de la carte
static void init_map_const(t_resources *resources, int num_of_lines)
{
	resources->game_map->map_height = num_of_lines;
	resources->game_map->map_length = -1; // La longueur de la carte sera déterminée plus tard
	resources->game_map->usual_texture_height = 32;
	resources->game_map->usual_texture_width = 32;
	resources->game_map->floor = NULL;
	resources->game_map->wall = NULL;
	resources->game_map->wall_map = NULL;
	resources->game_map->exit = NULL;
}

// Lit et traite chaque ligne de la carte
void read_and_process_lines(int fd, t_resources *resources, int num_of_lines)
{
	char *line;
	int current_line;

	current_line = 0;
	init_map_const(resources, num_of_lines);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (!process_line(line, resources, num_of_lines, current_line))
		{
			// En cas d'erreur, libérer la ligne et fermer le fichier
			free(line);
			close(fd);
			return;
		}
		free(line);
		current_line++;
	}
	close(fd); // Fermer le fichier après avoir traité toutes les lignes
}
