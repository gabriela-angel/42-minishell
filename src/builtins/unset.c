/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:28:05 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/13 17:05:20 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_key(const char *key)
{
	size_t	i;

	i = 1;
	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	remove_env_var(const char *key)
{
	char	**env;
	size_t	len;
	int		i;

	env = get_envp(NULL);
	if (!env)
		return ;
	len = ft_strlen(key);
	i = 0;
	while (env[i] && (ft_strncmp(env[i], key, len) != 0 || env[i][len] != '='))
		i++;
	if (env[i])
	{
		free(env[i]);
		while (env[i + 1])
		{
			env[i] = env[i + 1];
			i++;
		}
		env[i] = NULL;
	}
}

int	exec_unset(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (is_valid_key(args[i]))
			remove_env_var(args[i]);
		i++;
	}
	return (0);
}
