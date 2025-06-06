/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:28:47 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/06 16:25:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Imprime as variáveis de ambiente com '='.
 */
int	exec_env(char **args, char **env)
{
	int	i;

	if (args[1])
	{
		ft_printf_fd(2, "env: too many arguments\n");
		return (FAILURE);
	}
	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			ft_printf_fd(1, "%s\n", env[i]);
		i++;
	}
	return (SUCCESS);
}

char	*get_var_from_env(const char *key, char **env)
{
	size_t	klen;
	int		i;

	if (!key)
		return ("");
	klen = ft_strlen(key);
	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], key, klen) && env[i][klen] == '=')
			return (&env[i][klen + 1]);
		i++;
	}
	return ("");
}
