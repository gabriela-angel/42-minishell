/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:33:24 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/26 18:48:55 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Executa um nó logico || (OR)
static void	exec_or_node(t_tree *node, char ***env)
{
	execute_tree(node->left, env);
	if (exit_status(-1) != SUCCESS && exit_status(-1) < 128)
		execute_tree(node->right, env);
}

// Executa um nó logico && (AND)
static void	exec_and_node(t_tree *node, char ***env)
{
	execute_tree(node->left, env);
	if (exit_status(-1) == SUCCESS)
		execute_tree(node->right, env);
}

// Executa um subshell (comandos entre parênteses)
static void	exec_subshell(t_tree *node, char ***env)
{
	int		status;
	pid_t	pid;
	t_token	*current;
	t_tree	*subshell;

	pid = fork();
	if (pid < 0)
		exit(handle_error("fork"));
	if (pid == 0)
	{
		current = node->token;
		while (current->next)
			current = current->next;
		current->prev->next = NULL;
		current = node->token->next;
		subshell = get_tree(current);
		if (subshell)
			execute_tree(subshell, env);
		ft_gc_exit();
		exit(exit_status(-1));
	}
	wait_for_child(pid, &status);
}

// Executa a árvore de comandos
void	execute_tree(t_tree *node, char ***env)
{
	if (!node)
		return ;
	if (node->token->type == TK_AND)
		exec_and_node(node, env);
	else if (node->token->type == TK_OR)
		exec_or_node(node, env);
	else if (node->token->type == TK_PIPE)
		exec_pipe_node(node, env);
	else if (node->token->type >= TK_REDIR_OUT_APP \
		&& node->token->type <= TK_REDIR_OUT)
		exec_simple_command(node->token, env);
	else if (node->token->type == TK_OPEN_PARENTHESIS)
		exec_subshell(node, env);
	else
		exec_simple_command(node->token, env);
}

int	minishell_exec(t_tree *tree, char ***env)
{
	if (!tree)
		return (FAILURE);
	execute_tree(tree, env);
	return (SUCCESS);
}