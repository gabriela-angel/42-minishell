/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:28:54 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/07 11:33:01 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int handle_token_type(t_tree *root)
{
	if (root->command->token.type == TK_AND)
		return (execute_and(root->left, root->right));
	else if (root->command->token.type == TK_OR)
		return (execute_or(root->left, root->right));
	else if (root->command->token.type == TK_PIPE)
		return (execute_pipe(root->left, root->right));
	else if (root->command->token.type >= TK_REDIR_OUT_APP
		&& root->command->token.type <= TK_REDIR_OUT)
		return (execute_redirect(root->left, root->right, root->command->token.type));
	else if (root->command->token.type == TK_OPEN_PARENTHESIS)
		return (execute_block(root));
	else
	{
		handle_error("Unexpected token type");
		return (FAILURE);
	}
}

int executor(t_tree *root)
{
	if (!root || !root->command)
		return (SUCCESS);
	return (handle_token_type(root));
}

int execute_and(t_tree *left, t_tree *right)
{
	int exit_status;

	exit_status = set_exit_status(executor(left));
	if (exit_status == SUCCESS)
		return (set_exit_status(executor(right)));
	return (exit_status);
}

int execute_or(t_tree *left, t_tree *right)
{
	int exit_status;

	exit_status = set_exit_status(executor(left));
	if (exit_status != SUCCESS && *get_exit_status() < 128)
		return (set_exit_status(executor(right)));
	return (exit_status);
}

static void prepare_tokens_for_block(t_tree *root, t_tk_list **tokens_copy, t_tk_list **current)
{
	if (!root || !root->command || !root->command->next)
		return;
	*tokens_copy = root->command->next;
	*current = *tokens_copy;
	while (*current && (*current)->next)
		*current = (*current)->next;
	if (*current && (*current)->prev)
		(*current)->prev->next = NULL;
}

static void execute_child_block(t_tk_list *tokens_copy, t_tree **block_root)
{
    int exit_status;

    if (!tokens_copy || !block_root)
        exit(handle_error("Invalid arguments to execute_child_block"));

    *block_root = get_tree(tokens_copy, BRANCH_ROOT); // Substituindo parser por get_tree
    if (*block_root)
    {
        exit_status = executor(*block_root);
        ft_gc_exit();
        exit(exit_status);
    }
    ft_gc_exit();
    exit(handle_error("get_tree"));
}

int execute_block(t_tree *root)
{
	t_tree *block_root = NULL;
	t_tk_list *tokens_copy;
	t_tk_list *current;
	int exit_status;
	int pid;

	pid = fork();
	if (pid == -1)
		return (handle_error("fork"), FAILURE);
	if (pid == 0)
	{
		prepare_tokens_for_block(root, &tokens_copy, &current);
		execute_child_block(tokens_copy, &block_root);
	}
	wait_child_status(pid, &exit_status);
	return (exit_status);
}
