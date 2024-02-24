/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:05:21 by ebaillot          #+#    #+#             */
/*   Updated: 2024/02/24 17:49:01 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);

int	ft_putchar_p(char c);

int	ft_putstr_p(char *s);

int	ft_print_pointer(void *ptr);

int	ft_putnbr_p(int nb);

int	ft_putnbr_base_p(unsigned long nbr, char *base);

int	get_variadic(char *t, va_list *args);

#endif