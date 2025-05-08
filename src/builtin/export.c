/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:15:07 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/07 14:18:32 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_export_args(char **args)
{
	int		i;
	int		status;
	char	*key;
	char	*equal_sign;

	status = 0;
	i = 0;
	while (args[++i])
	{
		if (!is_valid_identifier(args[i], args[0]) && ++status)
			continue;
		key = get_key(args[i]);
		equal_sign = ft_strchr(args[i], '=');
		set_env(args[i], key, equal_sign ? equal_sign + 1 : NULL);
	}
	return (status);
}

int	execute_export(t_tree *command_tree)
{
	char	**args;
	int		status;

	if (!command_tree || !command_tree->command)
		return (handle_error("invalid command tree"));
	args = get_cmd_and_args(command_tree->command);
	if (!args[1])
		return (print_environ_sorted(), EXIT_SUCCESS);
	status = process_export_args(args);
	return (set_exit_status(!!status));
}


char	*get_key(char *arg)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (ft_strdup(arg));
	else
		return (ft_substr(arg, 0, equal_sign - arg));
}

int	is_valid_identifier(char *str, char *cmd_name)
{
	if (*str != '=' && !ft_isdigit(*str) && *str != '\0')
	{
		while (*str && *str != '=' && (ft_isalnum(*str) || *str == '_'))
			str++;
		if (*str == '=' || !*str)
			return (1);
	}
	ft_printf_fd(STDERR_FILENO, "%s: not a valid identifier\n", cmd_name);
	set_exit_status(FAILURE);
	return (0);
}

int	is_env_key_present(char *key)
{
	int		i;
	char	*env_key;
	char	**env;

	env = *get_my_env();
	i = -1;
	while (env[++i])
	{
		env_key = get_key(env[i]);
		if (!ft_strcmp(key, env_key))
		{
			free(env_key);
			return (1);
		}
		free(env_key);
	}
	return (0);
}

int	is_key_without_value(char *key)
{
	int		i;
	char	*env_key;
	char	**env;

	env = *get_my_env();
	i = -1;
	while (env[++i])
	{
		if (!ft_strchr(env[i], '='))
		{
			env_key = get_key(env[i]);
			if (!ft_strcmp(key, env_key))
			{
				free(env_key);
				return (1);
			}
			free(env_key);
		}
	}
	return (0);
}
