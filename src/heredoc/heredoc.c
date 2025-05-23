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

static int	write_to_heredoc(int fd, char *end_condition, int is_expandable)
{
	char	*line;
	char	*expanded_line;

	line = readline("> ");
	if (!line)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: warning: here-document\
 delimited by end-of-file (wanted '%s')\n", end_condition);
		return (SUCCESS);
	}
	ft_gc_add(line);
	if (ft_strcmp(line, end_condition) == SUCCESS)
		return (SUCCESS);
	if (is_expandable)
	{
		expanded_line = expand_var(line);
		ft_gc_free(line);
		line = expanded_line;
	}
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	return (FAILURE);
}

static int	init_heredoc(t_token *token, int *fd, char **file_name,
		t_bool *is_expandable)
{
	int		*heredoc_counter;
	char	*suffix;

	*is_expandable = FALSE;
	heredoc_counter = get_heredoc_counter();
	suffix = ft_itoa((*heredoc_counter)++);
	*file_name = ft_strjoin("/tmp/.heredoc", suffix);
	free(suffix);
	ft_gc_add(*file_name);
	*fd = open(*file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*fd < 0)
		return (FAILURE);
	if (!ft_strchr(token->value, '\"') && !ft_strchr(token->value, '\''))
		*is_expandable = TRUE;
	else
		token->value = remove_quotes(token->value);
	return (SUCCESS);
}

static int	heredoc_child(t_token *token, int *pipe_fd)
{
	int		fd;
	char	*file_name;
	char	buffer[1024];
	ssize_t	bytes_read;
	t_bool	is_expandable;
	char	*end_condition;

	end_condition = token->next->value;
	signal(SIGINT, handle_heredoc_sigint);
	close(pipe_fd[0]);
	if (init_heredoc(token, &fd, &file_name, &is_expandable) != SUCCESS)
		_exit(FAILURE);
	while (42)
		if (write_to_heredoc(fd, end_condition, is_expandable) == SUCCESS)
			break ;
	close(fd);
	fd = open(file_name, O_RDONLY);
	if (fd >= 0)
	{
		bytes_read = 1;
		while (bytes_read > 0)
		{
			bytes_read = read(fd, buffer, 1024);
			if (bytes_read > 0)
				write(pipe_fd[1], buffer, bytes_read);
		}
		close(fd);
	}
	close(pipe_fd[1]);
	_exit(SUCCESS);
}

static int	finish_heredoc_parent(int default_stdin, int *pipe_fd, pid_t pid)
{
	int	status;

	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipe_fd[0]);
		dup2(default_stdin, STDIN_FILENO);
		exit_status(130);
		ft_printf_fd(1, "\n");
		return (FAILURE);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(pipe_fd[0]);
		return (FAILURE);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	return (SUCCESS);
}

int	handle_heredoc(t_token *token)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		default_stdin;

	default_stdin = dup(STDIN_FILENO);
	if (pipe(pipe_fd) < 0)
		return (FAILURE);
	signal(SIGINT, SIG_IGN);
	if ((pid = fork()) < 0)
		return (FAILURE);
	if (pid == 0)
	{
		signal(SIGINT, handle_heredoc_sigint);
		heredoc_child(token, pipe_fd);
	}
	signal(SIGINT, SIG_IGN);
	if (finish_heredoc_parent(default_stdin, pipe_fd, pid))
		return (FAILURE);
	signal(SIGINT, SIG_DFL);
	return (SUCCESS);
}
