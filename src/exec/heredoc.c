/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:01:13 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/15 18:03:04 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int	write_heredoc(const char *delimiter, int write_fd)
{
	char	*line;

	signal(SIGINT, handle_heredoc_sigint);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf_fd(1, "Heredoc: warning: EOF received (expected '%s')\n", delimiter);
			return (1);
		}
		if (ft_strcmp(line, delimiter) == 0)
		break;
		ft_printf_fd(write_fd, "%s\n", line);
		ft_gc_free(line);
	}
	ft_gc_free(line);
	signal(SIGINT, SIG_DFL);
	return (0);
}

static int	handle_heredoc_child(t_token *token, int *pipe_fd)
{
	signal(SIGINT, handle_heredoc_sigint);
	close(pipe_fd[0]);
	if (write_heredoc(token->next->value, pipe_fd[1]) == 1)
		_exit(1);
	close(pipe_fd[1]);
	_exit(0);
}

static int	handle_heredoc_parent(int *pipe_fd, pid_t pid)
{
	int	status;

	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipe_fd[0]);
		g_exit_status = 130;
		ft_printf_fd(1, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return (1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(pipe_fd[0]);
		return (1);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	return (0);
}

int	handle_heredocs(t_token *token)
{
	int		pipe_fd[2];
	pid_t	pid;

	while (token)
	{
		if (token->type == TK_REDIR_HDOC && token->next)
		{
			if (pipe(pipe_fd) < 0)
				return (1);
			pid = fork();
			if (pid == 0)
				handle_heredoc_child(token, pipe_fd);
			if (handle_heredoc_parent(pipe_fd, pid))
				return (1);
		}
		token = token->next;
	}
	return (0);
}
