/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:11:54 by ebaillot          #+#    #+#             */
/*   Updated: 2024/02/24 17:48:52 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_variadic(char *t, va_list *args)
{
	int	count;

	count = 0;
	if (*t == 'c')
		count += ft_putchar_p(va_arg(*args, int));
	else if (*t == 's')
		count += ft_putstr_p(va_arg(*args, char *));
	else if (*t == 'p')
		count += ft_print_pointer(va_arg(*args, void *));
	else if (*t == 'd' || *t == 'i')
		count += ft_putnbr_p(va_arg(*args, int));
	else if (*t == 'u')
		count += ft_putnbr_base_p(va_arg(*args, unsigned int), "0123456789");
	else if (*t == 'x')
		count += ft_putnbr_base_p(va_arg(*args, unsigned int),
				"0123456789abcdef");
	else if (*t == 'X')
		count += ft_putnbr_base_p(va_arg(*args, unsigned int),
				"0123456789ABCDEF");
	else if (*t == '%')
		count += ft_putchar_p('%');
	else
		count += ft_putchar_p(*t);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += get_variadic((char *)format, &args);
		}
		else
		{
			count += ft_putchar_p(*format);
		}
		format++;
	}
	va_end(args);
	return (count);
}

/* int main()
{
	int				i;
	char			c;
	char			str[] = "Hello, World!";
	int				num;
	char			*null_str;
	int				int_num;
	unsigned int	uint_num;
	int				hex_num;

	c = 'A';
	num = 12345;
	null_str = NULL;
	int_num = -42;
	uint_num = 42;
	hex_num = 0x2a;
	i = ft_printf("Character: %c\n", c);
	printf("Printed characters: %d\n", i);
	i = ft_printf("String: %s\n", str);
	printf("Printed characters: %d\n", i);
	i = ft_printf("Pointer: %p\n", &num);
	printf("Printed characters: %d\n", i);
	i = ft_printf("Combo: %c, %s, %p\n", 'X', "test", &num);
	printf("Printed characters: %d\n", i);
	i = ft_printf("Special: %c%c%c\n", '\n', '\t', '\0');
	printf("Printed characters: %d\n", i);
	i = ft_printf("Empty string: %s\n", "");
	printf("Printed characters: %d\n", i);
	i = ft_printf("Null pointer: %s\n", null_str);
	printf("Printed characters: %d\n", i);
	i = ft_printf("Null pointer address: %p\n", NULL);
	printf("Printed characters: %d\n", i);
	i = ft_printf("Integer: %d\n", int_num);
	printf("Printed characters: %d\n", i);
	i = ft_printf("Unsigned Integer: %u\n", uint_num);
	printf("Printed characters: %d\n", i);
	i = ft_printf("Hexadecimal (lowercase): %x\n", hex_num);
	printf("Printed characters: %d\n", i);
	i = ft_printf("Hexadecimal (uppercase): %X\n", hex_num);
	printf("Printed characters: %d\n", i);
	i = ft_printf("Percent sign: %%\n");
	printf("Printed characters: %d\n", i);
	return (0);
}
*/