/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sheep_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:05:56 by edouard           #+#    #+#             */
/*   Updated: 2024/02/24 17:33:09 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sheep_draw_layer(t_resources *res, int y, int x)
{
	res->sheep->y = y;
	res->sheep->x = x;
	draw_sheep(&res->data, res->sheep);
}
