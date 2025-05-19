/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:53:33 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/19 13:40:38 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	long	nbr;
	int		counter;

	counter = 0;
	nbr = n;
	if (nbr < 0)
	{
		counter += ft_putchar_fd('-', fd);
		nbr = nbr * -1;
	}
	if (nbr > 9)
		counter += ft_putnbr_fd(nbr / 10, fd);
	counter += ft_putchar_fd(nbr % 10 + '0', fd);
	return (counter);
}
