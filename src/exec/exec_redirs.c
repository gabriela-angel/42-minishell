/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:27:27 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/31 17:16:38 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int apply_redirections(t_token *token)
{
	while (token)
	{
		if (token->type == TK_REDIR_OUT || token->type == TK_REDIR_OUT_APP)
		{
			int flags = O_CREAT | O_WRONLY
					  | (token->type == TK_REDIR_OUT_APP ? O_APPEND : O_TRUNC);
			int fd = open(token->next->value, flags, 0644);
			if (fd < 0)
				return (FAILURE);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (token->type == TK_REDIR_IN)
		{
			int fd = open(token->next->value, O_RDONLY);
			if (fd < 0)
				return (FAILURE);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		token = token->next;
	}
	return (SUCCESS);
}
