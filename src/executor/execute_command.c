/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:25:21 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/08 11:13:47 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_command(t_tree *cmd_node)
{
	int pid;
	int exit_status;

	if (!cmd_node || !cmd_node->command)
		return (SUCCESS);
	if (is_builtin(cmd_node->command))
		return (execute_builtin(cmd_node));
	pid = fork();
	if (pid == -1)
		return (handle_error("fork"));
	setup_fork_signal_handlers(pid);
	if (pid == 0)
	{
		run_command(cmd_node->command);
		exit(EXIT_FAILURE);
	}
	wait_child_status(pid, &exit_status);
	return (exit_status);
}

void run_command(t_tk_list *tokens)
{
	char **cmd_and_args = get_cmd_and_args(tokens);
	char *cmd_path = get_cmd_path(tokens);

	if (execve(cmd_path, cmd_and_args, __environ) == -1)
	{
		throw_error(cmd_path);
		free_env();
		ft_gc_exit();
		exit(127);
	}
}

char *get_cmd_path(t_tk_list *tokens)
{
	if (ft_strchr(tokens->token.value, '/'))
		return (tokens->token.value);
	return (search_in_path(tokens));
}

char *search_in_path(t_tk_list *tokens)
{
	char **paths = ft_split(getenv("PATH"), ':');
	char *cmd_path;
	int i = 0;

	if (!paths)
		exit(handle_error("failed to retrieve PATH"));
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(cmd_path, tokens->token.value);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		i++;
	}
	return (NULL);
}

char **get_cmd_and_args(t_tk_list *tokens)
{
	t_tk_list *current = tokens;
	char **cmd_and_args = ft_malloc(sizeof(char *) * (token_lst_get_size(tokens) + 1));
	int i = 0;

	if (!cmd_and_args)
		exit(handle_error("failed to allocate memory"));
	while (current)
	{
		cmd_and_args[i++] = current->token.value;
		current = current->next;
	}
	cmd_and_args[i] = NULL;
	return (cmd_and_args);
}
