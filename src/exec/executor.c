/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:33:24 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/23 17:05:42 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_or_node(t_tree *node)
{
	execute_tree(node->left);
	if (exit_status(-1) != SUCCESS && exit_status(-1) < 128)
		execute_tree(node->right);
}

static void	exec_and_node(t_tree *node)
{
	execute_tree(node->left);
	if (exit_status(-1) == SUCCESS)
		execute_tree(node->right);
}

static void	exec_subshell(t_tree *node)
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
			execute_tree(subshell);
		ft_gc_exit();
		exit(exit_status(-1));
	}
	wait_for_child(pid, &status);
}

static int	exec_redirection_node(t_tree *node)
{
	int		saved_stdin;
	int		saved_stdout;
	t_bool	err;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (node->token->type == TK_REDIR_HDOC)
		err = handle_heredoc(node->token);
	else
		err = process_heredoc_and_redirections(node->token, saved_stdin);
	if (!err && node->left && node->left->token)
		execute_tree(node->left);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	if (err)
		return (FAILURE);
	return (SUCCESS);
}

int	execute_tree(t_tree *node)
{
	if (!node)
		return (FAILURE);
	if (node->token->type == TK_AND)
		exec_and_node(node);
	else if (node->token->type == TK_OR)
		exec_or_node(node);
	else if (node->token->type == TK_PIPE)
		exec_pipe_node(node);
	else if (node->token->type >= TK_REDIR_OUT_APP \
		&& node->token->type <= TK_REDIR_OUT)
		return (exec_redirection_node(node));
	else if (node->token->type == TK_OPEN_PARENTHESIS)
		exec_subshell(node);
	else
		exec_simple_command(node->token);
	return (SUCCESS);
}
