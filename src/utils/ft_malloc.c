/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:52:06 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/03 23:04:46 by gangel-a         ###   ########.fr       */
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
	mlc->next = ft_calloc(1, sizeof(t_malloc));
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
	t_malloc	*mlc;
	t_malloc	*tmp;

	if (!ptr)
		return ;
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
	t_malloc	*mlc;
	t_malloc	*tmp;

	mlc = get_malloc_item();
	while (mlc->next)
	{
		if (mlc->ptr)
			free(mlc->ptr);
		tmp = mlc->next;
		mlc->ptr = tmp->ptr;
		mlc->next = tmp->next;
		free(tmp);
	}
	mlc->ptr = NULL;
	mlc->next = NULL;
}

t_bool	ft_gc_add(void *ptr)
{
	t_malloc	*mlc;

	if (!ptr)
		return (FALSE);
	mlc = get_malloc_item();
	while (mlc->next)
	{
		if (mlc->ptr == ptr)
			return (TRUE);
		mlc = mlc->next;
	}
	mlc->next = ft_calloc(1, sizeof(t_malloc));
	if (!mlc->next)
		return (FALSE);
	mlc->ptr = ptr;
	return (TRUE);
}

void	ft_gc_free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		ft_gc_free(matrix[i]);
		i++;
	}
	ft_gc_free(matrix);
	return ;
}
