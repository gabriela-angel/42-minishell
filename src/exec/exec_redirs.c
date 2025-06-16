/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:27:27 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/15 22:30:52 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir_out(t_token *token)
{
	int		flags;
	int		fd;

	flags = O_CREAT | O_WRONLY;
	if (token->type == TK_REDIR_OUT_APP)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(token->next->value, flags, 0644);
	if (fd < 0)
	{
		ft_printf_fd(2, "minishell: %s: %s\n",
			token->next->value, strerror(errno));
		exit_status(1);
		return (FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

static int	open_redir_in(t_token *token)
{
	int	fd;

	fd = open(token->next->value, O_RDONLY);
	if (fd < 0)
	{
		ft_printf_fd(2, "minishell: %s: %s\n",
			token->next->value, strerror(errno));
		exit_status(1);
		return (FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (SUCCESS);
}

int	apply_redirections(t_token *token)
{
	while (token)
	{
		if (token->type == TK_REDIR_OUT
			|| token->type == TK_REDIR_OUT_APP)
		{
			if (open_redir_out(token) == FAILURE)
				return (FAILURE);
		}
		else if (token->type == TK_REDIR_IN)
		{
			if (open_redir_in(token) == FAILURE)
				return (FAILURE);
		}
		token = token->next;
	}
	return (SUCCESS);
}
