/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:57:44 by gangel-a          #+#    #+#             */
/*   Updated: 2025/06/16 16:58:25 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_control_operator(t_token *current)
{
	if (current->prev == NULL
		|| current->prev->type <= TK_PIPE
		|| current->prev->type == TK_OPEN_PARENTHESIS)
		return (ft_printf_fd(2,
				"minishell: syntax error near unexpected token `%s'\n",
				current->value));
	if (current->next == NULL
		|| current->next->type <= TK_PIPE
		|| current->next->type == TK_CLOSE_PARENTHESIS)
		return (ft_printf_fd(2,
				"minishell: syntax error near unexpected token `%s'\n",
				current->value));
	return (SUCCESS);
}

static int	check_redirector(t_token *current)
{
	if (current->next == NULL)
		return (ft_printf_fd(2,
				"minishell: syntax error near unexpected token `newline'\n"));
	if (current->next->type != TK_WORD)
		return (ft_printf_fd(2,
				"minishell: syntax error near unexpected token `%s'\n",
				current->next->value));
	return (SUCCESS);
}

static int	check_parenthesis(t_token *current)
{
	if (current->type == TK_OPEN_PARENTHESIS)
	{
		if (current->prev != NULL && current->prev->type > TK_OPEN_PARENTHESIS)
			return (ft_printf_fd(2,
					"minishell: syntax error near unexpected token `%s'\n",
					current->value));
		if (current->next == NULL || current->next->type <= TK_PIPE)
			return (ft_printf_fd(2,
					"minishell: syntax error near unexpected token `%s'\n",
					current->value));
	}
	else if (current->type == TK_CLOSE_PARENTHESIS)
	{
		if (current->prev == NULL || (current->prev->type != TK_WORD
				&& current->prev->type != TK_CLOSE_PARENTHESIS))
			return (ft_printf_fd(2,
					"minishell: syntax error near unexpected token `%s'\n",
					current->value));
		if (current->next != NULL && (current->next->type == TK_WORD))
			return (ft_printf_fd(2,
					"minishell: syntax error near unexpected token `%s'\n",
					current->value));
	}
	return (SUCCESS);
}

int	validate_tokens(t_token *current)
{
	if (current->type <= TK_PIPE)
		return (check_control_operator(current));
	else if (current->type >= TK_REDIR_OUT_APP
		&& current->type <= TK_REDIR_OUT)
		return (check_redirector(current));
	else if (current->type == TK_OPEN_PARENTHESIS
		|| current->type == TK_CLOSE_PARENTHESIS)
		return (check_parenthesis(current));
	return (SUCCESS);
}
