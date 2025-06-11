/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:43:41 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/11 15:12:39 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Checa para ver se 'e um comando valido
static char	*verify_cmd(char *cmd, int *res)
{
	struct stat info;

	*res = 0;
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) != 0 || stat(cmd, &info) != 0)
		{
			if (errno == EACCES)
				*res = -1;
			else if (errno == ENOENT)
				*res = -2;
			else
				*res = -3;
			return (NULL);
		}
		if (S_ISDIR(info.st_mode))
		{
			*res = -3;
			return (NULL);
		}
		return (ft_strdup(cmd));
	}
	return (NULL);
}

// Concatena um descritor e um comando para formar um caminho completo
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

	// if (ft_strchr(cmd, '/'))
	// 	return (ft_strdup(cmd));
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

/* Executa um comando externo, localizando seu caminho e 
gerenciando o processo filho */
int	exec_external(char **argv)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;
	int		res;

	if (!argv[0] || argv[0][0] == '\0')
		return (0);
	res = 0;
	cmd_path = verify_cmd(argv[0], &res);
	if (!cmd_path)
	{
		if (res != 0)
			return (print_exec_exit_msg(argv[0], res));
		cmd_path = find_cmd_path(argv[0]);
		if (!cmd_path)
			return (print_exec_exit_msg(argv[0], -2));
	}
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
