/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sheep_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:05:56 by edouard           #+#    #+#             */
/*   Updated: 2024/02/13 14:23:46 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void sheep_draw_layer(t_resources *res, int y, int x)
{
	res->sheep->y = y;
	res->sheep->x = x;
	drawSheep(&res->data, res->sheep);
}