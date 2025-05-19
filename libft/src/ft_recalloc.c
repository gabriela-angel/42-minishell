/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:14:25 by gangel-a          #+#    #+#             */
/*   Updated: 2025/04/19 17:14:25 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_recalloc(void *ptr, size_t new_size, size_t old_size)
{
	void	*new_ptr;
	size_t	cpy_size;

	if (!ptr)
		return (ft_calloc(1, new_size));
	if (new_size == old_size)
		return (ptr);
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size < old_size)
		cpy_size = new_size;
	else
		cpy_size = old_size;
	new_ptr = ft_calloc(1, new_size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, cpy_size);
	free(ptr);
	return (new_ptr);
}
