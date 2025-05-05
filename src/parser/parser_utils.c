/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:24:43 by gangel-a          #+#    #+#             */
/*   Updated: 2025/04/29 18:24:43 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	is_subshell(t_tk_list *token_list, t_tree_branch branch)
{
	t_tk_list	*current;
	int			open_parenthesis;
	int			close_parenthesis;

	current = token_list;
	open_parenthesis = 0;
	close_parenthesis = 0;
	while (current)
	{
		if (current->token.type == TK_OPEN_PARENTHESIS)
			open_parenthesis++;
		else if (current->token.type == TK_CLOSE_PARENTHESIS)
			close_parenthesis++;
		else if (close_parenthesis == 0 && open_parenthesis == 0)
			break ;
		if (open_parenthesis == close_parenthesis && open_parenthesis != 0)
			return (TRUE);
		current = get_next_token(current, branch);
	}
	return (FALSE);
}

static t_tk_hierarchy	get_hierarchy(t_value_type type)
{
	else if (type == TK_OR || type == TK_AND)
		return (TK_OR_AND_HIERARCHY);
	if (type == TK_PIPE)
		return (TK_PIPE_HIERARCHY);
	else if (ft_isredirector(type)) //check if we want to use lexer utils or not
		return (TK_REDIR_HIERARCHY);
	else if (type == TK_OPEN_PARENTHESIS || type == TK_CLOSE_PARENTHESIS)
		return (TK_SUBSHELL_HIERARCHY);
	else if (type == TK_WORD)
		return (TK_CMD_HIERARCHY);
	else
		return (-1);
}

int	compare_priority(t_value_type current, t_value_type priority)
{
	t_tk_hierarchy	current_hierarchy;
	t_tk_hierarchy	priority_hierarchy;

	current_hierarchy = get_hierarchy(current);
	priority_hierarchy = get_hierarchy(priority);
	if (current_hierarchy > priority_hierarchy)
		return (1);
	else if (current_hierarchy < priority_hierarchy)
		return (-1);
	else
		return (0);
}
