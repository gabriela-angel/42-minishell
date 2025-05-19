/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbase_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:10:43 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/19 13:41:23 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_base_and_get_length(char *base)
{
	int	base_len;
	int	i;

	base_len = 0;
	while (base[base_len] != '\0')
	{
		if (base[base_len] == '+' || base[base_len] == '-')
			return (0);
		i = base_len + 1;
		while (base[i] != '\0')
		{
			if (base[base_len] == base[i])
				return (0);
			i++;
		}
		base_len++;
	}
	if (base_len < 2)
		return (0);
	return (base_len);
}

int	ft_putbase_fd(long nb, char *base, int fd)
{
	int		counter;
	long	baselen;

	if (!base)
		return (0);
	counter = 0;
	baselen = check_base_and_get_length(base);
	if (baselen == 0)
		return (0);
	if (nb < 0)
	{
		counter += write(fd, "-", 1);
		nb = nb * -1;
	}
	if (nb >= baselen)
		counter += ft_putbase_fd((nb / baselen), base, fd);
	counter += ft_putchar_fd(base[(nb % baselen)], fd);
	return (counter);
}
