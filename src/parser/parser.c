/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:13:13 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/06 15:01:33 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redir(t_tk_list *token_list, t_tree *tree)
{
    t_tk_list	*current;
    t_tk_list	*redir;

    current = token_list;
    while (current)
    {
        if (ft_isredirector(current->token))
        {
            redir = current;
            if (redir->token.type == TK_REDIR_HDOC)
                tree->here_doc_fd = create_heredoc(redir->next->token.value);
            else
                tree->file = ft_sublist(redir, redir, redir->next); 
            break ;
        }
        current = current->next;
    }
}

static t_tk_list	*skip_subshell(t_tk_list *token_list, t_tree_branch branch)
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
        if (open_parenthesis == close_parenthesis && open_parenthesis != 0)
            return (get_next_token(current, branch));
        current = get_next_token(current, branch);
    }
    return (current);
}

static t_tk_list	*get_priority(t_tk_list *token_list, t_tree_branch branch)
{
    t_tk_list	*priority;
    t_tk_list	*current;

    priority = NULL;
    if (branch == BRANCH_ROOT || branch == BRANCH_LEFT)
        current = get_last_token(token_list);
    else
        current = token_list;
    if (is_subshell(current, branch))
        return (current);
    while (current)
    {
        if (current->token.type == TK_OPEN_PARENTHESIS || current->token.type == TK_CLOSE_PARENTHESIS)
            current = skip_subshell(current, branch);
        if (current->token.type == TK_AND || current->token.type == TK_OR)
            return (current);
        if (!priority || compare_priority(current->token.type, priority->token.type) == 1)
            priority = current;
        current = get_next_token(current, branch);
    }
    return (priority);
}

static t_tree_type	get_tree_type(t_value_type type)
{
    if (type == TK_PIPE)
        return (TREE_PIPE);
    else if (type == TK_AND)
        return (TREE_AND);
    else if (type == TK_OR)
        return (TREE_OR);
    else if (type == TK_REDIR_IN)
        return (TREE_REDIR_IN);
    else if (type == TK_REDIR_OUT)
        return (TREE_REDIR_OUT);
    else if (type == TK_REDIR_OUT_APP)
        return (TREE_REDIR_OUT_APP);
    else if (type == TK_REDIR_HDOC)
        return (TREE_REDIR_HDOC);
    else if (type == TK_OPEN_PARENTHESIS || type == TK_CLOSE_PARENTHESIS)
        return (TREE_SUBSHELL);
    else
        return (TREE_CMD);
}

t_tree	*get_tree(t_tk_list *token_list, t_tree_branch branch)
{
    t_tree		*tree;
    t_tk_list	*priority;

    if (!token_list)
        return (NULL);
    tree = ft_malloc(sizeof(t_tree));
    if (!tree)
        return (NULL);
    priority = get_priority(token_list, branch);
    tree->type = get_tree_type(priority->token.type);
    if (tree->type == TREE_CMD)
        tree->command = ft_sublist(token_list, token_list, NULL);
    else if (tree->type == TREE_SUBSHELL)
        tree->subshell = get_tree(ft_sublist(token_list, token_list->next,
            get_last_token(token_list)), BRANCH_ROOT);
    else if (ft_isredirector(priority->token))
        handle_redir(token_list, tree);
    else
    {
        tree->left = get_tree(ft_sublist(token_list, token_list, priority), BRANCH_LEFT);
        tree->right = get_tree(ft_sublist(token_list, priority->next, token_list), BRANCH_RIGHT);
    }
    return (tree);
}