/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:26:01 by gangel-a          #+#    #+#             */
/*   Updated: 2025/04/19 16:45:33 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_malloc	*get_malloc_item(void)
{
	static t_malloc	mlc;

	return (&mlc);
}

void	*ft_malloc(size_t size)
{
	t_malloc	*mlc;
	void		*ptr;

	mlc = get_malloc_item();
	while (mlc->next)
		mlc = mlc->next;
	ptr = ft_calloc(1, size);
	if (!ptr)
		return (NULL);
	mlc->ptr = ptr;
	mlc->next = ft_calloc(1, sizeof(t_mlc));
	if (!mlc->next)
	{
		free(ptr);
		mlc->ptr = NULL;
		return (NULL);
	}
	return (ptr);
}

void	ft_gc_free(void *ptr)
{
	t_mlc	*mlc;
	t_mlc	*tmp;

	mlc = get_malloc_item();
	while (mlc->next)
	{
		if (mlc->ptr == ptr)
		{
			free(mlc->ptr);
			tmp = mlc->next;
			mlc->ptr = tmp->ptr;
			mlc->next = tmp->next;
			free(tmp);
			return ;
		}
		mlc = mlc->next;
	}
}

void	ft_gc_exit(void)
{
	t_mlc	*mlc;
	t_mlc	*tmp;

	mlc = get_malloc_item();
	while (mlc->next)
	{
		free(mlc->ptr);
		tmp = mlc->next;
		mlc->ptr = tmp->ptr;
		mlc->next = tmp->next;
		free(tmp);
	}
	get_malloc_item()->ptr = NULL;
	get_malloc_item()->next = NULL;
}

t_bool	ft_gc_add(void *ptr)
{
	t_mlc	*mlc;

	mlc = get_malloc_item();
	while (mlc->next)
	{
		if (mlc->ptr == ptr)
			return (TRUE);
		mlc = mlc->next;
	}
	mlc->next = ft_calloc(1, sizeof(t_mlc));
	if (!mlc->next)
		return (FALSE);
	mlc->ptr = ptr;
	return (TRUE);
}
