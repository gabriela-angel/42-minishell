/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:27:27 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/20 22:41:20 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir(t_token *token)
{
	int	fd;

	if (token->type == TK_REDIR_IN)
		fd = open(token->next->value, O_RDONLY);
	else if (token->type == TK_REDIR_OUT)
		fd = open(token->next->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (token->type == TK_REDIR_OUT_APP)
		fd = open(token->next->value, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		return (-1);
	if (fd < 0)
		perror("open");
	return (fd);
}

int	apply_redirections(t_token *token)
{
	while (token)
	{
		if (token->type >= TK_REDIR_OUT && token->type <= TK_REDIR_HDOC)
		{
			if (token->type != TK_REDIR_HDOC)
			{
				int fd = open_redir(token);
				if (fd < 0)
					return (1);
				if (dup2(fd, (token->type == TK_REDIR_IN) ? STDIN_FILENO : STDOUT_FILENO) < 0)
				{
					perror("dup2");
					close(fd);
					return (1);
				}
				close(fd);
			}
			token = token->next;
		}
		token = token->next;
	}
	return (0);
}
