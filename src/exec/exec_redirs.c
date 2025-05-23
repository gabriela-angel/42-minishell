/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:27:27 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/22 20:05:27 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir(t_token *token, int redir_type, int *fd)
{
	if (redir_type == TK_REDIR_IN)
		*fd = open(token->value, O_RDONLY);
	else if (redir_type == TK_REDIR_OUT)
		*fd = open(token->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (redir_type == TK_REDIR_OUT_APP)
		*fd = open(token->value, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		*fd = -1;
	if (*fd < 0)
		return (handle_error(token->value));
	return (SUCCESS);
}

static int	dup2_files(t_token *token, int redir_type, int *fd)
{
	int	status;

	status = SUCCESS;
	if (open_redir(token, redir_type, fd) != SUCCESS)
		return (FAILURE);
	if (redir_type == TK_REDIR_IN)
		status = dup2(*fd, STDIN_FILENO);
	else if (redir_type == TK_REDIR_OUT || redir_type == TK_REDIR_OUT_APP)
		status = dup2(*fd, STDOUT_FILENO);
	if (status == -1)
	{
		close(*fd);
		return (handle_error("dup2"));
	}
	close(*fd);
	return (status);
}

void	exec_redirection(t_tree *left, t_tree *right, int redir_type, char ***env)
{
	int		fd;
	int		std_fd[2];
	char	*before_expansion;

	if (redir_type == TK_REDIR_HDOC)
	{
		exit_status(handle_heredoc(right->token));
		return ;
	}
	before_expansion = ft_strdup(right->token->value);
	expand_tokens(right);
	if ((*before_expansion != '\0' && !right->token) || right->token->next)
	{
		ft_printf_fd(STDERR_FILENO, "%s: ambiguous redirect\n",
			before_expansion);
		exit_status(SYNTAX_ERROR);
		free(before_expansion);
		return ;
	}
	free(before_expansion);
	std_fd[0] = dup(STDIN_FILENO);
	std_fd[1] = dup(STDOUT_FILENO);
	if (dup2_files(right->token, redir_type, &fd) != SUCCESS)
		return ;
	if (left && left->token)
		execute_tree(left, env);
	dup2(std_fd[0], STDIN_FILENO);
	dup2(std_fd[1], STDOUT_FILENO);
	close(std_fd[0]);
	close(std_fd[1]);
}
