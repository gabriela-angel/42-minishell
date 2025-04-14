/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:21:33 by gangel-a          #+#    #+#             */
/*   Updated: 2024/12/17 16:52:29 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_formats(va_list args, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len = ft_printchar((char)va_arg(args, int));
	else if (format == 's')
		len = ft_printstr(va_arg(args, char *));
	else if (format == 'p')
		len = ft_printptr((unsigned long)va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		len = ft_printnbr(va_arg(args, int));
	else if (format == 'u')
		len = ft_printunbr(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		len = ft_printhex(va_arg(args, unsigned int), format);
	else
		len = ft_printchar(format);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		out_len;
	va_list	args;

	if (!format)
		return (-1);
	i = -1;
	out_len = 0;
	va_start(args, format);
	while (format[++i])
	{
		if (format[i] == '%')
		{
			i++;
			out_len += handle_formats(args, format[i]);
		}
		else
			out_len += ft_printchar((int)format[i]);
	}
	va_end(args);
	return (out_len);
}
