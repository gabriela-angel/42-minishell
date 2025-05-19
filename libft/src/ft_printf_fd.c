/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:05:19 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/07 18:34:18 by acesar-m         ###   ########.fr       */
=======
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:09:23 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/14 23:58:51 by gangel-a         ###   ########.fr       */
>>>>>>> origin/gabi
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_format(const int fd, const char specifier, va_list args)
{
	if (specifier == 'c')
		return (ft_putchar_fd(va_arg(args, int), fd));
	else if (specifier == 's')
		return (ft_putstr_fd(va_arg(args, char *), fd));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr_fd(va_arg(args, int), fd));
	else if (specifier == '%')
		return (ft_putchar_fd('%', fd));
	else if (specifier == 'p')
		return (ft_putptr_fd(va_arg(args, long), fd));
	else if (specifier == 'u')
		return (ft_putnbr_fd((va_arg(args, unsigned int)), fd));
	else if (specifier == 'x')
		return (ft_putbase_fd((long)va_arg(args, unsigned int),
				"0123456789abcdef", fd));
	else if (specifier == 'X')
		return (ft_putbase_fd((long)va_arg(args, unsigned int),
				"0123456789ABCDEF", fd));
	else
		return (0);
}

int	ft_printf_fd(const int fd, const char *str, ...)
{
	va_list	args;
	int		len;

	if (fd < 0)
		return (-1);
	va_start(args, str);
	len = 0;
	while (*str)
	{
		if (*str == '%' && *(str + 1))
			len += print_format(fd, *(++str), args);
		else
			len += ft_putchar_fd(*str, fd);
		str++;
	}
	va_end(args);
	return (len);
}
