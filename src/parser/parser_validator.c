/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:57:44 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/19 21:35:33 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_control_operator(t_token *current)
{
	if (current->prev == NULL || current->prev->type <= TK_PIPE
		|| current->prev->type == TK_OPEN_PARENTHESIS || (current->prev->type <= TK_REDIR_OUT && current->prev->type >= TK_REDIR_OUT_APP))
		return (FAILURE);//create a function to set exit status to SYNTAX ERROR
	if (current->next == NULL || current->next->type <= TK_PIPE
		|| current->next->type == TK_CLOSE_PARENTHESIS || (current->next->type <= TK_REDIR_OUT && current->next->type >= TK_REDIR_OUT_APP))
		return (FAILURE);//create a function to set exit status to SYNTAX ERROR
	return (SUCCESS);
}

static int	check_redirector(t_token *current)
{
	if (current->next == NULL || current->next->type != TK_WORD)
		return (FAILURE);//create a function to set exit status to SYNTAX ERROR
	return (SUCCESS);
}

static int	check_parenthesis(t_token *current)
{
	if (current->type == TK_OPEN_PARENTHESIS)
	{
		if (current->prev != NULL && current->prev->type > TK_OPEN_PARENTHESIS)
			return (FAILURE);//create a function to set exit status to SYNTAX ERROR
		if (current->next == NULL || current->next->type <= TK_PIPE)
			return (FAILURE);//create a function to set exit status to SYNTAX ERROR
	}
	else if (current->type == TK_CLOSE_PARENTHESIS)
	{
		if (current->prev == NULL || (current->prev->type != TK_WORD && current->prev->type != TK_CLOSE_PARENTHESIS))
			return (FAILURE);//create a function to set exit status to SYNTAX ERROR
		if (current->next != NULL && (current->next->type == TK_WORD))
			return (FAILURE);//create a function to set exit status to SYNTAX ERROR
	}
	return (SUCCESS);
}

int	validate_tokens(t_token *current)
{
	if (current->type <= TK_PIPE)
		return(check_control_operator(current));
	else if (current->type <= TK_REDIR_OUT && current->type >= TK_REDIR_OUT_APP)
		return (check_redirector(current));
	else if (current->type == TK_OPEN_PARENTHESIS || current->type == TK_CLOSE_PARENTHESIS)
		return (check_parenthesis(current));
	return (SUCCESS);
}
