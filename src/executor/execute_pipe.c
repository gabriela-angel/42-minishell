/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:28:40 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/07 17:18:34 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_child(int fd, int *pipe, t_tree *node)
{
	int	exit_status;

	if (dup2(pipe[fd], fd) == -1)
		exit(handle_error("dup2"));
	close_pipe(pipe);
	exit_status = executor(node);
	ft_gc_exit();
	free_env();
	exit(exit_status);
}

int	execute_pipe(t_tree *left, t_tree *right)
{
	int	child_pid[2];
	int	pipe_fd[2];
	int	exit_status[2];

	if (pipe(pipe_fd) == -1)
		exit(handle_error("pipe"));
	child_pid[0] = fork();
	if (child_pid[0] == -1)
		exit(handle_error("fork"));
	setup_fork_signal_handlers(child_pid[0]);
	if (child_pid[0] == 0)
		execute_child(STDOUT_FILENO, pipe_fd, left);
	child_pid[1] = fork();
	if (child_pid[1] == -1)
		exit(handle_error("fork"));
	setup_fork_signal_handlers(child_pid[1]);
	if (child_pid[1] == 0)
		execute_child(STDIN_FILENO, pipe_fd, right);
	close_pipe(pipe_fd);
	wait_child_status(child_pid[0], &exit_status[0]);
	wait_child_status(child_pid[1], &exit_status[1]);
	if (exit_status[0] == SIGINT + 128)
		return (exit_status[0]);
	return (exit_status[1]);
}

void	wait_child_status(pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else if (*status == 1)
		return ;
	else if (WIFSIGNALED(*status))
	{
		if (*status == SIGINT)
			write(STDIN_FILENO, "\n", 1);
		*status = WTERMSIG(*status) + 128;
	}
}
