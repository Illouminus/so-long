/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:17:55 by ebaillot          #+#    #+#             */
/*   Updated: 2024/01/21 19:09:05 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_putstr_p(char *s)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (s == NULL)
	{
		return (ft_putstr_p("(null)"));
	}
	while (s[i])
	{
		count += ft_putchar_p(s[i]);
		i++;
	}
	return (count);
}
