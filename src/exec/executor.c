/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:33:24 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/19 21:36:04 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static t_bool	has_heredoc(t_token *tok)
{
	while (tok)
	{
		if (tok->type == TK_REDIR_HDOC)
			return (TRUE);
		tok = tok->next;
	}
	return (FALSE);
}

void	exec_simple_command(t_token *token, char ***env)
{
	char	**argv;
	int		saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	if (has_heredoc(token) && handle_heredoc(token))
	{
		exit_status(130);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		return ;
	}
	if (apply_redirections(token))
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		return ;
	}
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

void	exec_child_left(t_tree *left, char ***env, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execute_tree(left, env);
	ft_gc_exit();
}

void	exec_child_right(t_tree *right, char ***env, int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	execute_tree(right, env);
	ft_gc_exit();
}

void	exec_pipe_node(t_tree *node, char ***env)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		return ;
	pid1 = fork();
	if (pid1 == 0)
		exec_child_left(node->left, env, fd);
	pid2 = fork();
	if (pid2 == 0)
		exec_child_right(node->right, env, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	execute_tree(t_tree *node, char ***env)
{
	if (!node)
		return ;
	if (node->token->type == TK_PIPE)
		exec_pipe_node(node, env);
	else
		exec_simple_command(node->token, env);
}
