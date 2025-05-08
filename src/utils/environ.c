/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:31:06 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/08 11:36:21 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_environment_variables(void)
{
	char	**env_copy;
	int		i;

	if (!__environ)
		exit(handle_error("Environment not found"));
	i = 0;
	while (__environ[i])
		i++;
	*get_my_env() = ft_malloc(sizeof(char *) * (i + 1));
	env_copy = *get_my_env();
	if (!ft_gc_add(env_copy))
		exit(handle_error("failed to register memory"));
	i = -1;
	while (__environ[++i])
	{
		env_copy[i] = ft_strdup(__environ[i]);
		if (!ft_gc_add(env_copy[i]))
			exit(handle_error("failed to register memory"));
	}
	env_copy[i] = NULL;
}

void	free_env(void)
{
	int		i;
	char	**env;

	env = *get_my_env();
	if (!env)
		return;
	i = -1;
	while (env[++i])
		ft_gc_free(env[i]);
	ft_gc_free(env);
}

void	set_env(char *new_str, char *key, char *value)
{
	char	*env_var;

	env_var = getenv(key);
	if ((env_var || is_key_without_value(key)) && value != NULL)
		update_env(new_str, key);
	else if (!is_env_key_present(key))
		add_to_env(new_str);
}

void	add_to_env(char *str)
{
	char	**new_env;
	int		i;
	char	**env;

	if (!str)
		return;
	env = *get_my_env();
	i = 0;
	while (env[i])
		i++;
	new_env = ft_malloc((i + 2) * sizeof(char *));
	if (!ft_gc_add(new_env))
		exit(handle_error("failed to register memory"));
	i = -1;
	while (env[++i])
		new_env[i] = env[i];
	new_env[i++] = ft_strdup(str);
	if (!new_env[i - 1] || !ft_gc_add(new_env[i - 1]))
	{
		ft_gc_free(new_env);
		exit(handle_error("failed to register memory"));
	}
	new_env[i] = NULL;
	ft_gc_free(env);
	*get_my_env() = new_env;
}

void	update_env(char *new_str, char *key)
{
	int		i;
	char	*env_key;
	char	*aux;
	char	**env;

	env = *get_my_env();
	i = -1;
	while (env[++i])
	{
		env_key = get_key(env[i]);
		if (!ft_strcmp(key, env_key))
		{
			aux = env[i];
			env[i] = ft_strdup(new_str);
			if (!ft_gc_add(env[i]))
				exit(handle_error("failed to register memory"));
			ft_gc_free(aux);
			ft_gc_free(env_key);
			break ;
		}
		ft_gc_free(env_key);
	*get_my_env() = env;
	__environ = env;
	}
}
