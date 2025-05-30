/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:37:58 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/30 11:05:13 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// Processa os redirecionamentos e heredocs associados ao token.
// Lida com heredocs e aplica redirecionamentos de entrada/saída.
// Retorna TRUE se ocorrer um erro ou se o comando não puder ser executado,
// caso contrário, retorna FALSE.
t_bool	process_heredoc_and_redirections(t_token *token, int saved_stdin)
{
	while (token)
	{
		if (token->type == TK_REDIR_HDOC)
		{
			if (handle_heredoc(token))
			{
				exit_status(130);
				dup2(saved_stdin, STDIN_FILENO);
				close(saved_stdin);
				return (TRUE);
			}
		}
		token = token->next;
	}
	if (apply_redirections(token))
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		return (TRUE);
	}
	return (FALSE);
}

// Executa um comando simples (sem pipes ou operadores lógicos).
// Verifica se o comando é um builtin ou um comando externo e o executa.
// Libera a memória de `argv` e restaura o stdin original após a execução.
static void	execute_command(char **argv, char ***env, int saved_stdin)
{
	if (is_builtin(argv[0]))
		exit_status(exec_builtin(argv, env, exit_status(-1)));
	else
		exit_status(exec_external(argv, *env));
	ft_free_split(argv);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}

// Libera a memória e restaura o stdin original após a execução de um comando simples.
// Usada para garantir que os recursos sejam liberados corretamente em caso de erro.
static void	cleanup_and_restore(int saved_stdin, char **argv)
{
	ft_free_split(argv);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}

// Executa um comando simples (sem pipes ou operadores lógicos).
// Processa heredocs e redirecionamentos, converte tokens em `argv` e executa o comando.
// Restaura o stdin original após a execução.
void	exec_simple_command(t_token *token, char ***env)
{
	int		saved_stdin;
	char	**argv;
	t_token	*cur;
	int		i;

	saved_stdin = dup(STDIN_FILENO);
	cur = token;
	while (cur)
		cur = cur->next;
	if (process_heredoc_and_redirections(token, saved_stdin))
		return ;
	argv = convert_token_to_argv(token);
	i = 0;
	while (argv && argv[i])
		i++;
	if (!argv || !argv[0])
	{
		cleanup_and_restore(saved_stdin, argv);
		return ;
	}
	execute_command(argv, env, saved_stdin);
}
