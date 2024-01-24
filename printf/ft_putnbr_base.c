/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:27:55 by ebaillot          #+#    #+#             */
/*   Updated: 2024/01/21 19:11:53 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int ft_strlen_p(char *str)
{
	unsigned int length;

	length = 0;
	while (str[length])
	{
		length++;
	}
	return (length);
}

int check_base(char *base)
{
	int i;
	char prev_char;
	char current_char;

	i = 0;
	prev_char = '\0';
	if (ft_strlen_p(base) < 1)
		return (0);
	while (base[i])
	{
		current_char = base[i];
		if (current_char == prev_char)
			return (0);
		else if (base[i] == '+' || base[i] == '-')
			return (0);
		prev_char = current_char;
		i++;
	}
	return (1);
}

int ft_putnbr_base_p(unsigned long nbr, char *base)
{
	unsigned long length_base;
	int count;

	count = 0;
	length_base = ft_strlen_p(base);
	if (!check_base(base))
		return (0);
	if (nbr >= length_base)
	{
		count += ft_putnbr_base_p(nbr / length_base, base);
		count += ft_putnbr_base_p(nbr % length_base, base);
	}
	else
	{
		count += ft_putchar_p(base[nbr % length_base]);
	}
	return (count);
}
