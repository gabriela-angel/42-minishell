/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:33:24 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/30 10:37:13 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Executa um nó lógico || (OR).
// Executa o nó da esquerda e, se o status de saída for diferente de SUCCESS,
// executa o nó da direita.
static void	exec_or_node(t_tree *node, char ***env)
{
	execute_tree(node->left, env);
	if (exit_status(-1) != SUCCESS && exit_status(-1) < 128)
		execute_tree(node->right, env);
}

// Executa um nó lógico && (AND).
// Executa o nó da esquerda e, se o status de saída for SUCCESS,
// executa o nó da direita.
static void	exec_and_node(t_tree *node, char ***env)
{
	execute_tree(node->left, env);
	if (exit_status(-1) == SUCCESS)
		execute_tree(node->right, env);
}

// Executa um subshell (comandos entre parênteses).
// Cria um processo filho para executar os comandos do subshell.
// Gera uma nova árvore de comandos para o subshell e a executa.
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

// Executa a árvore de comandos.
// Identifica o tipo do nó atual (AND, OR, PIPE, REDIREÇÃO, etc.)
// e chama a função apropriada para executar o nó.
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
	{
		int saved_stdin = dup(STDIN_FILENO);
		if (node->token->type == TK_REDIR_HDOC)
			handle_heredoc(node->token);
		else
			process_heredoc_and_redirections(node->token, saved_stdin);
		execute_tree(node->left, env);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		return ;
	}
	else if (node->token->type == TK_OPEN_PARENTHESIS)
		exec_subshell(node, env);
	else
		exec_simple_command(node->token, env);
}

// Função principal para executar a árvore de comandos.
// Verifica se a árvore é válida e chama a função `execute_tree`.
// Retorna SUCCESS em caso de sucesso ou FAILURE em caso de erro.
int	minishell_exec(t_tree *tree, char ***env)
{
	if (!tree)
		return (FAILURE);
	execute_tree(tree, env);
	return (SUCCESS);
}