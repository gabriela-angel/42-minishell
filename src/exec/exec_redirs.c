/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:27:27 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/15 14:00:11 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
		return (0);
	if (fd < 0)
	{
		perror("minishell");
		return (1);
	}
	if (token->type == TK_REDIR_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_redirections(t_token *token)
{
	while (token)
	{
		if (token->type >= TK_REDIR_OUT && token->type <= TK_REDIR_HDOC)
		{
			if (!token->next || open_redir(token))
				return (1);
			token = token->next;
		}
		token = token->next;
	}
	return (0);
}
