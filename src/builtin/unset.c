/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:22:55 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/07 14:25:50 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_new_env(char *key_to_delete, char **cur_env)
{
	int		i;
	int		j;
	char	*env_key;
	char	**new_env;

	i = 0;
	while (cur_env[i])
		i++;
	new_env = (char **)ft_malloc((i + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = -1;
	j = -1;
	while (cur_env[++i])
	{
		env_key = get_key(cur_env[i]);
		if (ft_strcmp(key_to_delete, env_key))
			new_env[++j] = cur_env[i];
		else
			ft_gc_free(cur_env[i]);
		ft_gc_free(env_key);
	}
	new_env[++j] = NULL;
	return (new_env);
}

void	delete_env_key(char *key_to_delete)
{
	char	**cur_env;
	char	**new_env;

	cur_env = *get_my_env();
	new_env = create_new_env(key_to_delete, cur_env);
	if (!new_env)
		return ;
	ft_gc_free(cur_env);
	*get_my_env() = new_env;
	__environ = new_env;
}

int	execute_unset(t_tree *command_tree)
{
	int		i;
	char	**args;
	int		status;

	i = 0;
	status = 0;
	if (!command_tree || !command_tree->command)
		return (handle_error("invalid command tree"));
	args = get_cmd_and_args(command_tree->command);
	if (!args[1])
		return (set_exit_status(status));
	while (args[++i])
	{
		if (!is_valid_identifier(args[i], args[0]) && ++status)
			continue ;
		delete_env_key(get_key(args[i]));
	}
	return (set_exit_status(!!status));
}
