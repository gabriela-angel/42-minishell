/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fT_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:18:47 by gangel-a          #+#    #+#             */
/*   Updated: 2025/06/13 17:18:47 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <limits.h>

static int	is_overflow(unsigned long long nb, int sign)
{
	if (sign == 1 && nb > (unsigned long long)LLONG_MAX)
		return (1);
	if (sign == -1 && nb > (unsigned long long)(LLONG_MAX) + 1)
		return (1);
	return (0);
}

int	ft_strtoll_check(const char *nptr, long long *out)
{
	long long	nb;
	int			i;
	int			sign;

	i = 0;
	nb = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		sign = 1 - 2 * (nptr[i++] == '-');
	if (!nptr[i])
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		if (is_overflow(nb, sign))
			return (0);
		i++;
	}
	if (nptr[i])
		return (0);
	*out = nb * sign;
	return (1);
}
