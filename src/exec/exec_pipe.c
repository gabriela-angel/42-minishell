/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:08:04 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/20 23:08:04 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_child(pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		exit_status(WEXITSTATUS(*status));
	else if (WIFSIGNALED(*status))
		exit_status(WTERMSIG(*status) + 128);
	else
		exit_status(1);
}

static void	exec_child_left(t_tree *left, char ***env, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execute_tree(left, env);
	ft_gc_exit();
}

static void	exec_child_right(t_tree *right, char ***env, int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	execute_tree(right, env);
	ft_gc_exit();
}

void	exec_pipe_node(t_tree *node, char ***env)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		exit_status[2];

	if (pipe(fd) == -1)
		return ;
	pid1 = fork();
	if (pid1 == 0)
		exec_child_left(node->left, env, fd);
	pid2 = fork();
	if (pid2 == 0)
		exec_child_right(node->right, env, fd);
	close(fd[0]);
	close(fd[1]);
	wait_for_child(pid1, &exit_status[0]);
	wait_for_child(pid2, &exit_status[1]);
}
