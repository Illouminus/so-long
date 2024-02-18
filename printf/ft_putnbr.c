/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:14:09 by ebaillot          #+#    #+#             */
/*   Updated: 2024/01/21 19:10:32 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_putnbr_p(int nb)
{
	int count;

	count = 0;
	if (nb == -2147483648)
	{
		count += ft_putchar_p('-');
		count += ft_putchar_p('2');
		count += ft_putnbr_p(147483648);
	}
	else if (nb < 0)
	{
		count += ft_putchar_p('-');
		nb = -nb;
		count += ft_putnbr_p(nb);
	}
	else if (nb > 9)
	{
		count += ft_putnbr_p(nb / 10);
		count += ft_putnbr_p(nb % 10);
	}
	else
	{
		count += ft_putchar_p(nb + '0');
	}
	return (count);
}
