/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:44:05 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/19 21:35:33 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void split_list(t_tree *tree, t_token *list, t_token *tk_to_cut);
static void split_redir(t_tree *tree, t_token *list, t_token *tk_to_cut);

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
		return (NULL); // Handle error fail to build syntax tree
	branch_tree(tree, token_list);
	return (tree);
}

static void	split_redir(t_tree *tree, t_token *list,	t_token *tk_to_cut)
{
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
	tree->right = build_tree(tk_to_cut->next);
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
		return ; //CREATE ERROR FUNC TO PRINT ERROR MSG "FAILED TO BUILD SYNTAX TREE"
	sublist = ft_cutlist(tk_to_cut->next, NULL);
	if (!sublist)
		return ; //CREATE ERROR FUNC TO PRINT ERROR MSG "FAILED TO BUILD SYNTAX TREE"
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
			ft_printf_fd(2, "Syntax error in tokens\n"); // Depuração
			return (NULL);
		}
		current = current->next;
	}
	tree = build_tree(token_list);
	if (!tree)
		ft_printf_fd(2, "Failed to build syntax tree\n"); // Depuração
	return (tree);
}
