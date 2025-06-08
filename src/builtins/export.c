/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:42:53 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/08 17:47:30 by gangel-a         ###   ########.fr       */
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
	new_env = ft_malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		new_env[i] = ft_strdup(env[i]);
		ft_gc_add(new_env[i]);
	}
	new_env[i] = ft_strdup(assignment);
	ft_gc_add(new_env[i]);
	new_env[i + 1] = NULL;
	return (new_env);
}

int	exec_export(char **args)
{
	int		i;
	int		status;
	char	**new_env;
	char	**env;
	
	env = get_envp(NULL);
	status = 0;
	i = 1;
	while (args[i])
	{
		if (valid_assignment(args[i]))
		{
			new_env = extend_env_array(args[i], env);
			env = get_envp(new_env);
			ft_gc_free_matrix(new_env);
		}
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
