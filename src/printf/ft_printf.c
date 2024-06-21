/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-21 13:17:43 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-06-21 13:17:43 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static void	put_s(char *str, int *len)
{
	if (!str)
		str = "(null)";
	while (*str)
		*len += write(1, str++, 1);
}

static void put_n(long long int num, int base, int *len)
{
	char *div = "0123456789abcdef";

	if (num < 0)
	{
		num *= -1;
		*len += write(1, "-", 1);
	}
	if (num > base)
		put_n(num / base, base, len);
	*len += write(1, &div[num % base], 1);
}

int	ft_printf(const char *format, ...)
{
	int len;
	va_list ap;

	len = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 's')
				put_s(va_arg(ap, char *), &len);
			else if (*format == 'd')
				put_n(va_arg(ap, int), 10, &len);
			else if (*format == 'x')
				put_n(va_arg(ap, unsigned int), 16, &len);
		}
		else
			len += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (len);
}