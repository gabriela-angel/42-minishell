/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:37:58 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/02 16:53:07 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Processa os redirecionamentos e heredocs associados ao token.
// Lida com heredocs e aplica redirecionamentos de entrada/saída.
// Retorna TRUE se ocorrer um erro ou se o comando não puder ser executado,
// caso contrário, retorna FALSE.
t_bool	process_heredoc_and_redirections(t_token *token, int saved_stdin)
{
	t_token	*cur;

	cur = token;
	while (cur)
	{
		if (cur->type == TK_REDIR_HDOC && handle_heredoc(cur))
		{
			exit_status(130);
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
			return (TRUE);
		}
		cur = cur->next;
	}
	cur = token;
	if (apply_redirections(cur))
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		return (TRUE);
	}
	return (FALSE);
}

static void	child_simple_command(t_token *token, char ***env, int saved_stdin)
{
	char	**argv;

	if (process_heredoc_and_redirections(token, saved_stdin))
		_exit(exit_status(-1));
	argv = convert_token_to_argv(token);
	if (!argv || !*argv)
		_exit(exit_status(-1));
	if (is_builtin(argv[0]))
		exit_status(exec_builtin(argv, env, exit_status(-1)));
	else
		exit_status(exec_external(argv, *env));
	ft_free_split(argv);
	_exit(exit_status(-1));
}

static void	perform_fork(t_token *token, char ***env,
				int saved_stdin, int saved_stdout)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
		child_simple_command(token, env, saved_stdin);
	else
	{
		waitpid(pid, &status, 0);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
	}
}

void	exec_simple_command(t_token *token, char ***env)
{
	int		saved_stdin;
	int		saved_stdout;
	char	**argv;
	int		status;

	argv = convert_token_to_argv(token);
	if (is_builtin(argv[0]))
	{
		status = exec_builtin(argv, env, exit_status(-1));
		exit_status(status);
		ft_free_split(argv);
		return ;
	}
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	perform_fork(token, env, saved_stdin, saved_stdout);
	ft_free_split(argv);
}
