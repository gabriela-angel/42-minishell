/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:43:41 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/11 14:32:47 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_path_cmd(char *dir, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	res = ft_strjoin_free(tmp, cmd);
	ft_gc_add(res);
	return (res);
}

static char	*find_cmd_path(char *cmd)
{
	char	**paths;
	char	*path_env;
	char	*full;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = getenv("PATH");
	if (!path_env)
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

static int	wait_and_handle_status(int status, char *cmd_path)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			ft_printf_fd(1, "\n");
		signal(SIGINT, handle_sigint);
		ft_gc_free(cmd_path);
		return (128 + WTERMSIG(status));
	}
	signal(SIGINT, handle_sigint);
	ft_gc_free(cmd_path);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (FAILURE);
}

int exec_external(char **argv)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;
	DIR		*dir;

	cmd_path = find_cmd_path(argv[0]);
	if (!cmd_path)
	{
		ft_printf_fd(2, "%s: command not found\n", argv[0]);
		return (127);
	}
	dir = opendir(cmd_path);
	if (dir)
	{
		closedir(dir);
		ft_printf_fd(2, "minishell: %s: Is a directory\n", cmd_path);
		ft_gc_free(cmd_path);
		exit_status(126);
		return (126);
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		exec_child_process(cmd_path, argv);
	waitpid(pid, &status, 0);
	return (wait_and_handle_status(status, cmd_path));
}
