/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:17:33 by gpico-co          #+#    #+#             */
/*   Updated: 2024/10/17 11:45:56 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "ft_printf.h"

void	ft_flags(const char *str_char, va_list args, unsigned int *counter)
{
	int				result_c;
	unsigned long	ptr_value;

	if (*str_char == 'c')
	{
		result_c = va_arg(args, int);
		*counter += write(1, &result_c, 1);
	}
	else if (*str_char == 'u')
		ft_putunbr(va_arg(args, unsigned int), counter);
	else if (*str_char == 'd' || *str_char == 'i')
		ft_putnbr(va_arg(args, int), counter);
	else if (*str_char == 's')
		ft_putstr(va_arg(args, const char *), counter);
	else if (*str_char == 'x' || *str_char == 'X')
		ft_puthex(va_arg(args, unsigned int), *str_char, counter);
	else if (*str_char == 'p')
	{
		ptr_value = (unsigned long)va_arg(args, void *);
		if (ptr_value != 0)
			*counter += write(1, "0x", 2);
		ft_puthexp (ptr_value, counter);
	}
}

int	ft_printf(const char *str, ...)
{
	va_list			args;
	unsigned int	i;
	unsigned int	result;

	if (!str)
		return (-1);
	i = 0;
	result = 0;
	va_start(args, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '%')
				result += write(1, "%", 1);
			else
				ft_flags(&str[i + 1], args, &result);
			i++;
		}
		else
			result += write(1, &str[i], 1);
		i++;
	}
	va_end(args);
	return (result);
}
