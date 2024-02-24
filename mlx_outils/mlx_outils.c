/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_outils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:57:41 by ebaillot          #+#    #+#             */
/*   Updated: 2024/02/24 15:39:19 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	load_map(t_resources *res)
{
	ft_load_textures(res);
	init_and_load_sheep(res);
	ft_put_textures(res);
}
