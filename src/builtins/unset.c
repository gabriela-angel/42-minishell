/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:28:05 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/02 15:20:43 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_key(const char *key)
{
	int	i;

	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (SUCCESS);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

int	exec_unset(char **args, char ***env)
{
	int	i;
	int	j;

	i = 0;
	while (args[++i])
	{
		if (is_valid_key(args[i]) == FAILURE)
		{
			j = 0;
			while ((*env)[j]
				&& (!ft_strncmp((*env)[j], args[i], ft_strlen(args[i]))
				|| (*env)[j][ft_strlen(args[i])] == '='))
				j++;
			if ((*env)[j])
			{
				ft_gc_free((*env)[j]);
				while ((*env)[j])
					(*env)[j] = (*env)[j + 1];
			}
		}
	}
	return (SUCCESS);
}
