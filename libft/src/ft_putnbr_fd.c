/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:53:33 by gangel-a          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/07 13:08:02 by acesar-m         ###   ########.fr       */
=======
/*   Updated: 2025/05/18 20:15:02 by gangel-a         ###   ########.fr       */
>>>>>>> origin/gabi
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

<<<<<<< HEAD
int	ft_putnbr_fd(long nbr, int fd)
{
	int		counter;

	counter = 0;
=======
int	ft_putnbr_fd(int n, int fd)
{
	long	nbr;
	int		counter;

	counter = 0;
	nbr = n;
>>>>>>> origin/gabi
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
