/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:44:05 by gangel-a          #+#    #+#             */
/*   Updated: 2025/04/25 18:44:05 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*search_token_rev(t_token *token_list, t_value_type start_type, t_value_type end_type)
{
	t_token	*current;
	int		parenthesis;

	current = get_last_token(token_list);
	while (current)
	{
		if (current->type >= start_type && current->type <= end_type)
			return (current);
		if (current->type == TK_CLOSE_PARENTHESIS)
		{
			parenthesis = 1;
			while (parenthesis)
			{
				current = current->prev;
				if (current->type == TK_OPEN_PARENTHESIS)
					parenthesis--;
				else if (current->type == TK_CLOSE_PARENTHESIS)
					parenthesis++;
			}
		}
		current = current->prev;
	}
}


static void	branch_tree(t_tree *tree, t_token *token_list)
{
	t_token	*is_and_or;
	t_token	*is_pipe;
	t_token	*is_redir;

	is_and_or = search_token_rev(token_list, TK_AND, TK_OR);
	if (is_and_or)
		return (ft_sublist()); //we gotta alter this function a bit
	is_pipe = search_token_rev(token_list, TK_PIPE, TK_PIPE);
	if (is_pipe)
		return (ft_sublist()); //we gotta alter this function a bit
	is_redir = search_token(token_list, TK_REDIR_OUT_APP, TK_REDIR_OUT); // actually, the search for the redirect goes a bit different, so we need another function for that
	if (is_redir)
		return (ft_sublist()); //we gotta alter this function a bit
	else
		tree->token = token_list;
}

static t_tree	*build_tree(t_token *token_list)
{
	t_tree	*tree;

	tree = ft_malloc(sizeof(t_tree));
	if (!tree)
		return (NULL); // Handle error fail to build syntax tree
	branch_tree(tree, token_list);
	return (tree);
}

t_tree	*get_tree(t_token *token_list)
{
	t_tree	*tree;
	t_token	*current;
	
	if (!token_list)
		return (NULL);
	current = token_list;
	while (current)
	{
		if (validate_tokens(current) != SUCCESS)
			return (NULL); //create a function to set exit status to SYNTAX ERROR
		if (current->type == TK_REDIR_HEREDOC && current->next->type == TK_WORD)
			//create heredoc file
		current = current->next;
	}
	tree = build_tree(token_list);
	return (tree);
}
