/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:42:53 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/03 14:35:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	valid_assignment(const char *s)
{
	size_t	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (FALSE);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (FALSE);
		i++;
	}
	return (s[i] == '=');
}

static char	**extend_env_array(const char *assignment, char **env)
{
	size_t	len;
	char	**new_env;
	size_t	i;

	len = 0;
	while (env && env[len])
		len++;
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = ft_strdup(assignment);
	new_env[i + 1] = NULL;
	free(env);
	return (new_env);
}

int	exec_export(char **args, char ***env)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	while (args[i])
	{
		if (valid_assignment(args[i]))
			*env = extend_env_array(args[i], *env);
		else
		{
			ft_printf_fd(2, "export: `%s': not a valid identifier\n",
				args[i]);
			status = 1;
		}
		i++;
	}
	return (status);
}
