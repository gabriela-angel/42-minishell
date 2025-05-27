/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:33:24 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/27 14:31:45 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_simple_command(t_token *token, char ***env)
{
	char	**argv;
	int		saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	argv = convert_token_to_argv(token);
	if (!argv || !argv[0])
	{
		ft_free_split(argv);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		return ;
	}
	if (is_builtin(argv[0]))
		exit_status(exec_builtin(argv, env, exit_status(-1)));
	else
		exit_status(exec_external(argv, *env));
	ft_free_split(argv);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}

static void	exec_or_node(t_tree *node, char ***env)
{
	execute_tree(node->left, env);
	if (exit_status(-1) != SUCCESS && exit_status(-1) < 128)
		execute_tree(node->right, env);
}

static void	exec_and_node(t_tree *node, char ***env)
{
	execute_tree(node->left, env);
	if (exit_status(-1) == SUCCESS)
		execute_tree(node->right, env);
}

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
		exec_redirection(node->left, node->right, node->token->type, env);
	else if (node->token->type == TK_OPEN_PARENTHESIS)
		exec_subshell(node, env);
	else
		exec_simple_command(node->token, env);
}
