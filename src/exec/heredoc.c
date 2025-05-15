/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:01:13 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/14 11:12:10 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int	write_heredoc(const char *delimiter, int write_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		ft_gc_free(line);
	}
	ft_gc_free(line);
	return (0);
}

int	handle_heredocs(t_token *token)
{
	int		pipe_fd[2];

	while (token)
	{
		if (token->type == TK_REDIR_HDOC && token->next)
		{
			if (pipe(pipe_fd) < 0)
				return (1);
			if (write_heredoc(token->next->value, pipe_fd[1]))
				return (1);
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
			token = token->next;
		}
		token = token->next;
	}
	return (0);
}
