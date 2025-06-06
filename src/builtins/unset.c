/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:28:05 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/06 16:18:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_valid_key(const char *key)
{
	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	for (int i = 1; key[i]; i++)
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
	return (1);
}

int exec_unset(char **args, char ***env)
{
	int i = 1;
	while (args[i])
	{
		if (is_valid_key(args[i]))
		{
			size_t len = ft_strlen(args[i]);
			int j = 0;
			while ((*env)[j]
				&& (ft_strncmp((*env)[j], args[i], len) != 0
					|| (*env)[j][len] != '='))
				j++;
			if ((*env)[j])
			{
				ft_gc_free((*env)[j]);
				while ((*env)[j])
				{
					(*env)[j] = (*env)[j + 1];
					j++;
				}
			}
		}
		else
			ft_printf_fd(2, "unset: `%s': not a valid identifier\n", args[i]);
		i++;
	}
	return (0);
}
