/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:43:41 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/19 16:51:38 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static char	*join_path_cmd(char *dir, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, cmd);
	ft_gc_free(tmp);
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
			return (ft_free_split(paths), full);
		ft_gc_free(full);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

int	exec_external(char **argv, char **envp)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	cmd_path = find_cmd_path(argv[0]);
	if (!cmd_path)
	{
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, argv, envp);
		perror("minishell");
		ft_gc_exit();
	}
	waitpid(pid, &status, 0);
	ft_gc_free(cmd_path);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
