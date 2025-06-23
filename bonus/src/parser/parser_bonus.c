/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:44:05 by gangel-a          #+#    #+#             */
/*   Updated: 2025/06/23 19:48:09 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	split_list(t_tree *tree, t_token *list, t_token *tk_to_cut);
static void	split_redir(t_tree *tree, t_token *list, t_token *tk_to_cut);

static void	branch_tree(t_tree *tree, t_token *token_list)
{
	t_token	*is_and_or;
	t_token	*is_pipe;
	t_token	*is_redir;

	is_and_or = search_token_rev(token_list, TK_AND, TK_OR);
	if (is_and_or)
		return (split_list(tree, token_list, is_and_or));
	is_pipe = search_token_rev(token_list, TK_PIPE, TK_PIPE);
	if (is_pipe)
		return (split_list(tree, token_list, is_pipe));
	is_redir = search_token(token_list, TK_REDIR_OUT_APP, TK_REDIR_OUT);
	if (is_redir)
		return (split_redir(tree, token_list, is_redir));
	else
		tree->token = token_list;
}

static t_tree	*build_tree(t_token *token_list)
{
	t_tree	*tree;

	tree = ft_malloc(sizeof(t_tree));
	if (!tree)
	{
		perror("failed to build syntax tree");
		return (NULL);
	}
	branch_tree(tree, token_list);
	expand_tokens(tree);
	return (tree);
}

static void	split_redir(t_tree *tree, t_token *list,	t_token *tk_to_cut)
{
	t_token	*right_tk;

	if (!tree || !list || !tk_to_cut)
		return ;
	tree->token = tk_to_cut;
	if (list == tk_to_cut)
		list = ft_cutlist(list->next->next, NULL);
	else
	{
		tk_to_cut->prev->next = tk_to_cut->next->next;
		if (tk_to_cut->next->next)
			tk_to_cut->next->next->prev = tk_to_cut->prev;
		tk_to_cut->next->next = NULL;
	}
	tk_to_cut->prev = NULL;
	tk_to_cut->next->prev = NULL;
	right_tk = ft_malloc(sizeof(t_token));
	right_tk->type = tk_to_cut->next->type;
	right_tk->value = ft_strdup(tk_to_cut->next->value);
	ft_gc_add(right_tk->value);
	tree->right = build_tree(right_tk);
	tree->left = build_tree(list);
}

static void	split_list(t_tree *tree, t_token *list, t_token *tk_to_cut)
{
	t_token	*sublist;

	if (!tree || !list || !tk_to_cut)
		return ;
	sublist = NULL;
	tree->token = tk_to_cut;
	list = ft_cutlist(list, tk_to_cut);
	if (!list)
	{
		perror("failed to build syntax tree");
		return ;
	}
	sublist = ft_cutlist(tk_to_cut->next, NULL);
	if (!sublist)
	{
		perror("failed to build syntax tree");
		return ;
	}
	tk_to_cut->prev = NULL;
	tree->left = build_tree(list);
	tree->right = build_tree(sublist);
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
		{
			exit_status(SYNTAX_ERROR);
			return (NULL);
		}
		current = current->next;
	}
	tree = build_tree(token_list);
	return (tree);
}
