/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:43:41 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/24 10:50:07 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_cmd_path(char *cmd)
{
	char	**paths;
	char	*path_env;
	char	*full;
	int		i;

	path_env = get_var_from_env("PATH", get_envp(NULL));
	if (!path_env || *path_env == '\0')
		return (NULL);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths && paths[i])
	{
		full = join_path_cmd(paths[i], cmd);
		if (access(full, X_OK) == 0)
			return (ft_free_matrix(paths), full);
		ft_gc_free(full);
		i++;
	}
	ft_free_matrix(paths);
	return (NULL);
}

static void	exec_child_process(char *cmd_path, char **argv)
{
	char	**env;

	env = get_envp(NULL);
	setup_signals_child();
	execve(cmd_path, argv, env);
	perror("minishell");
	ft_gc_exit();
}

static int	prepare_external(char **argv, char **cmd_path)
{
	int	res;

	if (!argv[0] || argv[0][0] == '\0')
		return (0);
	res = 0;
	*cmd_path = verify_cmd(argv[0], &res);
	if (!*cmd_path)
	{
		if (res != 0)
			return (handle_err_exec(argv[0], res));
		*cmd_path = find_cmd_path(argv[0]);
		if (!*cmd_path)
			return (handle_err_exec(argv[0], -2));
	}
	return (1);
}

int	exec_external(char **argv)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;
	int		ready;

	ready = prepare_external(argv, &cmd_path);
	if (ready != 1)
		return (ready);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		exec_child_process(cmd_path, argv);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	ft_gc_free(cmd_path);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		ft_printf_fd(1, "\n");
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (FAILURE);
}
